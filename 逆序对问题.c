#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define FILENAME_LEN 21
#define INPUT_LEN 81
#define COMMAND_LEN 11
using namespace std;
//结点结构
struct FileNode 
{
	char filename[FILENAME_LEN];    //文件名/目录名
	int isdir;                      //目录文件识别标志
	int i_nlink;                    //文件的链接数
	int adr;                        //文件的地址
	struct FileNode *parent, *child;//指向父亲的指针和指向左孩子的指针
	struct FileNode *sibling_prev, *sibling_next;//指向前一个兄弟的指针和指向
	//后一个兄弟的指针.
};

void Init();                           //初始化文件树
int ParseCommand();                    //接受输入的命令并把其分解成操作名和路径文件名
void ExecuteCommand();                 //执行命令
int cdComd();                          //处理cd命令
int creatComd();                       //处理creat命令
int delComd();                         //处理del命令
int dirComd();                         //处理dir命令
int mdComd();                          //处理md命令
int rdComd();
int FindPath(char *ph);                //寻找参数ph所指向的路径
int FindFilename(char Para2[]);        //从参数Para2中找到要建立或删除的文件、目录名，并把指针只想其父亲结点
struct FileNode* CreateFileNode(char filename[],int isdir,int i_nlink);//创建结点
int GetInput(char* buffer,unsigned int buffer_len);//获取输入
int CheckCommand();//命令检查
int GetDir(int begin,char *path,char *curDir);//获取路径
void Trim(char *str);
struct FileNode *cp, *tp, *root;
char path[INPUT_LEN-COMMAND_LEN];//记录当前走过的路径
char Para1[COMMAND_LEN],Para2[INPUT_LEN-COMMAND_LEN];
char curpath[INPUT_LEN-COMMAND_LEN],tmppath[INPUT_LEN-COMMAND_LEN];
char filename[FILENAME_LEN],tmp;
unsigned int i,j;//int i,j;

//主函数
int main()
{
	printf("模拟文件管理系统\n");
	printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
    printf("\n--------------------------------------------------------------------------------\n");
	Init();//初始化文件树
	while(1)
	{   //printf("#");
		if(ParseCommand())//分解命令
			ExecuteCommand();//执行命令
	}
    return 0;
}

//执行命令子函数
void ExecuteCommand()
{
	int sign;
	//根据参数Para1调用相应的功能处理模块
	 if(strcmp(Para1,"cd")==0)   
		 sign=cdComd(); //cd命令
   else if(strcmp(Para1,"creat")==0) 
		sign=creatComd();//edit命令
   else if(strcmp(Para1,"md")==0)
	   sign=mdComd();
	else if(strcmp(Para1,"del")==0) 
		sign=delComd(); //del命令
	else if(strcmp(Para1,"rd")==0)
		sign=rdComd();
	else if(strcmp(Para1,"dir")==0) 
		sign=dirComd();          //dir命令
	else if(strcmp(Para1,"exit")==0)
		exit(0);                         //exit命令
	else
		printf("命令错误,请重试\n");  //命令输入不正确，报错
}

//创建结点
struct FileNode* CreateFileNode(char filename[],int isdir,int i_nlink)
{
	//申请结点空间
    struct FileNode* node=(struct FileNode*)malloc(sizeof(struct FileNode));
	//相应内容赋初值
    strcpy(node->filename,filename);
	node->isdir=isdir;
	node->i_nlink=i_nlink;
	node->parent=NULL;
	node->child=NULL;
	node->sibling_prev=NULL;
	node->sibling_next=NULL;
    return node;
}

//初始化文件树
void Init()
{
	struct FileNode *dir1Node,*dir2Node,
		*file1Node,*etcNode,*libNode,*userNode,
		*binNode2,*liuNode,*sunNode,*ftiNode;
	strcpy(path,"/"); //根目录写入当前路径
	//创建文件树的结点
	dir1Node=CreateFileNode("dir1",1,0);
	dir2Node=CreateFileNode("dir2",1,0);
	file1Node=CreateFileNode("file1",0,0);
	etcNode=CreateFileNode("etc",1,0);
	libNode=CreateFileNode("lib",1,0);
	userNode=CreateFileNode("user",1,0);
	binNode2=CreateFileNode("bin",1,0);
	liuNode=CreateFileNode("liu",1,0);
	sunNode=CreateFileNode("sun",1,0);
	ftiNode=CreateFileNode("fti",1,0);
	cp=tp=root=CreateFileNode("/",1,0);
	//结点相应内容赋值
	root->parent=NULL;
	root->child=dir1Node;
	root->sibling_prev=root->sibling_next=NULL;
	
	dir1Node->parent=root;
	dir1Node->child=NULL;
	dir1Node->sibling_prev=NULL;
	dir1Node->sibling_next=dir2Node;
	
	dir2Node->parent=NULL;
	dir2Node->child=libNode;
	dir2Node->sibling_prev=dir1Node;
	dir2Node->sibling_next=file1Node;
	
	file1Node->parent=NULL;
	file1Node->child=NULL;
	file1Node->sibling_prev=dir2Node;
	file1Node->sibling_next=etcNode;
	
	etcNode->parent=NULL;
	etcNode->child=NULL;
	etcNode->sibling_prev=file1Node;
	etcNode->sibling_next=NULL;
	
	libNode->parent=dir2Node;
	libNode->child=liuNode;
	libNode->sibling_prev=NULL;
	libNode->sibling_next=userNode;
	
	userNode->parent=NULL;
	userNode->child=NULL;
	userNode->sibling_prev=libNode;
	userNode->sibling_next=binNode2;
	
	binNode2->parent=NULL;
	binNode2->child=NULL;
	binNode2->sibling_prev=userNode;
	binNode2->sibling_next=NULL;
	
	liuNode->parent=libNode;
	liuNode->child=NULL;
	liuNode->sibling_prev=NULL;
	liuNode->sibling_next=sunNode;
	
	sunNode->parent=NULL;
	sunNode->child=NULL;
	sunNode->sibling_prev=liuNode;
	sunNode->sibling_next=ftiNode;
	
	ftiNode->parent=NULL;
	ftiNode->child=NULL;
	ftiNode->sibling_prev=sunNode;
	ftiNode->sibling_next=NULL;	
}

//获取文件或目录名，并把指针指向其父亲结点
int FindFilename(char Para2[])
{
	i=strlen(Para2)-1;
	j=0;
	
	while(Para2[i]!='/'&& i>=0)
	{	
		filename[j]=Para2[i];
		i--; j++;
	}
	filename[j]='\0';//获得逆序的文件或目录名，存入filename中
	if(i<0) Para2[i+1]='\0';
	else Para2[i]='\0';
	j--;
	//filename逆转，获得正确的文件或目录名
	for(i=0;i<strlen(filename)/2;i++,j--)
	{
		tmp=filename[i];
		filename[i]=filename[j];
		filename[j]=tmp;
	}
	//return filename[i];
	//查找路径
	if(strlen(Para2)>0)
	{
		int sign=FindPath(Para2);
		if(sign==0) 
			return 0;
	}
	return 1;
}

//缓冲区安全输入子函数
//如果输入超过buffer_len，则截取前buffer_len-1长度的输入，
//buffer_len处字符用'/0'代替
int GetInput(char* buffer,unsigned int buffer_len)
{
	unsigned int count=0;//int count=0;
	while(count<buffer_len)
	{
		if((buffer[count]=getchar())==10)
		{
			buffer[count]='\0';
			return count;
		}
		count++;
	}
	while(getchar()!=10);
	buffer[buffer_len-1]='\0';
	return -1;
}	

//分解命令子函数
int ParseCommand()
{
	char Inputs[INPUT_LEN];
	int i=0,j=0,ch;
	unsigned int k=0;//int k=0;
	
	printf("%s>",path);
	printf("#");
	//获取输入
	if(GetInput(Inputs,INPUT_LEN)==-1)
	{
		printf("输入行太长。\n");
		return 0;
	}

	Para1[0]=Para2[0]='\0';
	//获取参数Para1，即操作名
	while(Inputs[i]!=' '&&Inputs[i]!='\0' && i<COMMAND_LEN-1)
	{   
		Para1[i]=Inputs[i];
		i++;
	}//while
	Para1[i]='\0';
	
	//输入命令太长
	if(i==(COMMAND_LEN-1))return 1;
	
	//获取参数2，即路径文件名
	if(Inputs[i]!='\0')
	{    
		while(Inputs[i]==' ' && i<INPUT_LEN-1) i++;
		j=0;
		while(Inputs[i]!='\0'  && i<INPUT_LEN-1)
		{  
			Para2[j]=Inputs[i];
			i++; j++;
		}
		Para2[j]='\0';
	}
	Trim(Para1);
	Trim(Para2);
	
	//将操作名全部转换成小写字母
	for(k=0;k<strlen(Para1);k++)
	{
		ch=tolower((int)Para1[k]);
		Para1[k]=ch;
	}
	return 1;
}
//cd功能处理子函数
int cdComd()
{
	if(!CheckCommand()) //命令检查
		return 0;
	if(strcmp(Para2,"..")==0)
	{   //对cd..命令的处理
		int i;
		while(cp->sibling_prev)
			cp=cp->sibling_prev;
		if(cp->parent)
		{ cp=cp->parent; }//找到父亲结点
		else
		{ return 0;  }
		//对当前路径进行相应处理
		i=strlen(path);
		while(path[i]!='/'&&i>0) i--;
		if(i!=0)
			path[i]='\0';
		else
			path[i+1]='\0';
	}
	else {
		FindPath(Para2);//查找路径
	}
	printf("进入工作目录\n");
    printf("\n\n模拟文件管理系统\n");
	printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	return 1;
}
//命令处理子函数
void Trim(char *str)
{
	int begin,end;
	char *tmp;
	begin=0;
	end=strlen(str);
	//找到字符串第一个非空格的位置
	while(str[begin]==' '&&str[begin]!='\0')
		begin++;
    //去除字符串尾部空格
    while(str[--end]==' ');
	str[end+1]='\0';
	// 除去空格
	if(begin<end)
	{
		tmp=(char *)malloc((sizeof(char))*(end-begin+2));
		strcpy(tmp,&str[begin]);
		strcpy(str,tmp);
		free(tmp);
	}
}

//获取当前目录名子函数
int GetDir(int begin,char *path,char *curDir)
{
	int i=0;
	int len=strlen(path);
	while(!((path[begin]=='\\')||(path[begin]=='/'))&&begin<len)
	{  curDir[i++]=path[begin++];  }
	curDir[i]='\0';
	Trim(curDir);
	return begin+1;
}

//查找路径函数
int FindPath(char *ph)
{
	struct FileNode *temp; //struct FileNode *tp,*temp;
	char oldpath[INPUT_LEN-COMMAND_LEN];
	unsigned int i=0; //int i=0
	int sign=1;
	if(strcmp(ph,"/")==0)
	{     //ph是根目录
		cp=root;
		strcpy(path,"/");
		return 1;
	}
	temp=cp;
	strcpy(oldpath,path);//保留原路径和指针
	if(ph[0]=='/')
	{    //指针指向根目录的左孩子
		cp=root->child;
		i++; //滤过'/'
		strcpy(path,"/");
	}
	else {
		if(cp!=NULL&&cp!=root)
			strcat(path,"/");
		if(cp&&cp->child)
		{
			if(cp->isdir)
				cp=cp->child;//指针指向当前目录的左孩子
			else{
				printf("路径错误!\n");
				return 0;
			}
		}
	}
	while(i<=strlen(ph)&&cp) //继续查找指定路径，如遇到文件则报错
	{
		int j=0;
		if(ph[i]=='/'&&cp->child)
		{
			i++; //略过'/'
			if(cp->isdir)
				cp=cp->child; //继续查找下级目录
			else {
				printf("路径错误!\n");
				return 0;
			}
			strcat(path,"/");
		}
   // curpath 记录当前要找的路径名
		while(ph[i]!='/'&&i<=strlen(ph))
		{
			curpath[j]=ph[i];
			i++; j++;
		}
		curpath[j]='\0';
		while((strcmp(cp->filename,curpath)!=0||(cp->isdir!=1))&&cp->sibling_next!=NULL)
		{  cp=cp->sibling_next;  }
		if(strcmp(cp->filename,curpath)==0)
		{
			if(cp->isdir==0)
			{
				strcpy(path,oldpath);
				cp=temp;
				printf("是文件不是目录.\n");
				return 0;
			}
			strcat(path,cp->filename);
		}
		if(strcmp(cp->filename,curpath)!=0||cp==NULL)
		{
			strcpy(path,oldpath);
			cp=temp;
			printf("输入路径错误\n");
			return 0;
		}
	}
	return 1;
}

//创建文件子函数
int creatComd()
{ 
	
	struct FileNode * temp=CreateFileNode("",0,0);
	int sign;
	struct FileNode *tp;
	
	//路径不能为空
	if(strlen(Para2)==0)
	{
		printf("\n命令格式有错误.\n");
		return 0;
	}
	//长度检查
	if(strlen(Para2)>50)
	{
		printf("\n文件名过长\n");
		return 0;
	}
	//格式检查
	if (!(isalpha(Para2[0])||Para2[0]=='_'||Para2[0]=='\0'||Para2[0]=='/'))
	{
		printf("文件名格式有错!\n");/* 文件首字母可以为'字母'或'数字'或'_'或'/'或'回车'*/
		return 0;
	}
	
	//获取文件名
	sign=FindFilename(Para2);
	if(sign==0)
		return 0;
	
	if(cp->isdir!=1)//如当前指针指向的是文件，则报错
	{
		printf("you cannot edit a file in under a file!\n");
		return 0;
	}
	
	//创建文件结点，并插入到指定目录下
	tp=CreateFileNode("",1,0);
	strcpy(tp->filename,filename);
	tp->isdir=0;
	tp->i_nlink=0;
	if(cp->child==NULL)
	{	tp->parent=cp;
	tp->child=NULL;
	cp->child=tp;
	tp->sibling_prev=NULL;
	tp->sibling_next=NULL;
	}
	else
	{	temp=cp;
	   //用temp找到新结点插入处
	temp=temp->child;
	while(temp->sibling_next )//find the last sibing node
	{
		temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)==0&&temp->isdir==0)
		{
			printf("此文件名已存在\n");//重名报错
			return 0;
		}
	}//找到了最后一个结点

	temp->sibling_next=tp;
	tp->parent=NULL;
	tp->child=NULL;
	tp->sibling_prev=temp;
	tp->sibling_next=NULL;
	
	}
	printf("新建文件\n");
    printf("\n\n模拟文件管理系统\n");
    printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	
	return 1;
}

//删除文件子函数
int delComd()
{ 
	int sign;
	struct FileNode *temp;
	//参数不能为空
	if(strlen(Para2)==0)
	{
		printf("\n命令格式有错误.\n");
		return 0;
	}
	//获取文件名
	sign=FindFilename(Para2);
	if(sign==0) return 0;
	
	//用temp指向要删除的结点
	if(cp->child) 
	{
		temp=cp->child;
		while(temp->sibling_next && (strcmp(temp->filename,filename)!=0 || temp->isdir!=0))
			temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)!=0)
		{
			printf("不存在该文件!\n");
			return 0;
		}
	}
	else
	{
		printf("不存在该文件!\n");
		return 0;
	}
	//要删除的不能是目录
	if(temp->isdir!=0)
	{
		printf("ERROR!该命令只能删除文件,不可删除目录!\n");
		return 0;
	}
	//如仍有用户使用该文件，则不能删除
	if(temp->i_nlink!=0)
	{
		printf("还有用户共享了该文件,不能删除!\n");
		return 0;
	}
	//删除工作
    if(temp->parent==NULL)//不是第一个孩子
	{
		temp->sibling_prev->sibling_next=temp->sibling_next;
		if(temp->sibling_next)//处理是最后一个兄弟的情况
			temp->sibling_next->sibling_prev=temp->sibling_prev;
		temp->sibling_prev=temp->sibling_next=NULL;
		printf("删除完毕");
	}//if
	else//第一个孩子
	{ 
		if(temp->sibling_next)//处理是最后一个兄弟的情况
			temp->sibling_next->parent=temp->parent;
		temp->parent->child=	temp->sibling_next;
        printf("删除完毕\n");
	}//else
	
	free(temp);
    printf("\n\n模拟文件管理系统\n");
	printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	
	return 1;
}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

int mdComd()
{ 
	
	struct FileNode * temp,*tp;
		temp=CreateFileNode("",1,0);
	int sign;
	
	//参数不能为空
	if(strlen(Para2)==0)
	{
		printf("\n命令格式有错误.\n");
		return 0;
	}
	//长度检查
	if(strlen(Para2)>50)
	{
		printf("\n目录名过长\n");
		return 0;
	}
	//格式检查
	if (!(isalpha(Para2[0])||Para2[0]=='_'||Para2[0]=='\0'||Para2[0]=='/'))
	{
		printf("目录名格式有错!\n");/* 目录首字母可以为'字母'或'数字'或'/'*/
		return 0;
	}
	
	//获取目录名
	sign=FindFilename(Para2);
	if(sign==0)
		return 0;
	
	if(cp->isdir!=1)//如当前指针指向的是文件，则报错
	{
		printf("you cannot edit a directory in under a file!\n");
		return 0;
	}
	
	//创建目录结点，并插入到指定目录下
	tp=CreateFileNode(filename,1,0);
	
	if(cp->child==NULL)
	{	tp->parent=cp;
	tp->child=NULL;
	cp->child=tp;
	tp->sibling_prev=NULL;
	tp->sibling_next=NULL;
	}
	else
	{	temp=cp;
	   //用temp找到新结点插入处
	temp=temp->child;
	while(temp->sibling_next )//find the last sibing node
	{
		temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)==0&&temp->isdir==1)
		{
			printf("此目录名已存在\n");//重名报错
			return 0;
		}
	}//找到了最后一个结点

	temp->sibling_next=tp;
	tp->parent=NULL;
	tp->child=NULL;
	tp->sibling_prev=temp;
	tp->sibling_next=NULL;
    printf("创建目录\n");
	
	}
    printf("\n\n模拟文件管理系统\n");
    printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	
	return 1;
}
int rdComd()
{ 
	int sign;
	struct FileNode *temp;
	char cmd[2];
	//命令检查
	if(!CheckCommand())
		return 0;

	//获取目录名
	sign=FindFilename(Para2);
	if(sign==0) return 0;
	
	//用temp指向要删除的结点
	if(cp->child) 
	{
		temp=cp->child;
		while(temp->sibling_next && (strcmp(temp->filename,filename)!=0 || temp->isdir!=1))
			temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)!=0)
		{
			printf("不存在该目录!\n");
			return 0;
		}
	}
	else
	{
		printf("不存在该目录!\n");
		return 0;
	}
	//要删除的不能是文件
	if(temp->isdir!=1)
	{
		printf("ERROR!该命令只能删除目录,不可删除文件!\n");
		return 0;
	}
	//如仍有用户使用该目录，则不能删除
	if(temp->child)
	{
		printf("\n该目录不为空，您确定要删除吗？Y/N!\n");
	    GetInput(cmd,2);
		if(strcmp(cmd,"n")==0||strcmp(cmd,"N")==0)
			return 0;
	}
	//删除工作
    if(temp->parent==NULL)//不是第一个孩子
	{
		temp->sibling_prev->sibling_next=temp->sibling_next;
		if(temp->sibling_next)//处理是最后一个兄弟的情况
			temp->sibling_next->sibling_prev=temp->sibling_prev;
		temp->sibling_prev=temp->sibling_next=NULL;
	}//if
	else//第一个孩子
	{ 
		if(temp->sibling_next)//处理是最后一个兄弟的情况
			temp->sibling_next->parent=temp->parent;
		temp->parent->child=	temp->sibling_next;
	}//else
    printf("删除目录\n");
    printf("\n\n模拟文件管理系统\n");
	printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	free(temp);
	
	return 1;
}


//显示目录子函数
int dirComd()
{
	if(strlen(Para2)>0)
	{
		int sign=FindPath(Para2);//查找路径
		if(sign==0)
		{
			return 0;
		}
		else
		{
			printf("\n%s>", path);
		}
	}
	
	if(cp!=root)
		printf("   <DIR>             %s\n","..");
	
	if(cp->child==NULL) 
	{
		return 0;//指定目录为空
	}
	
	tp=cp;
	//指定目录不为空，显示其所有子目录及文件名
	tp=tp->child;
	while(tp)
	{
		if(tp->isdir)
			printf("   <DIR>             %s\n",tp->filename);
		else
			printf("   <FILE>            %s\n",tp->filename);
		tp=tp->sibling_next;
	}
	printf("显示目录\n");
    printf("\n\n模拟文件管理系统\n");
    printf("\ncd 改变目录; creat 创建文件; del 删除文件;\n");
	printf("dir 显示目录; md 创建目录; rd 删除目录; exit 退出.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	return 0;//后加的
}
int CheckCommand()
{
	if(strlen(Para2)==0)
	{
		printf("命令语法不正确.\n");
		return 0;
	}
	return 1;
}

