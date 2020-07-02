#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define FILENAME_LEN 21
#define INPUT_LEN 81
#define COMMAND_LEN 11
using namespace std;
//���ṹ
struct FileNode 
{
	char filename[FILENAME_LEN];    //�ļ���/Ŀ¼��
	int isdir;                      //Ŀ¼�ļ�ʶ���־
	int i_nlink;                    //�ļ���������
	int adr;                        //�ļ��ĵ�ַ
	struct FileNode *parent, *child;//ָ���׵�ָ���ָ�����ӵ�ָ��
	struct FileNode *sibling_prev, *sibling_next;//ָ��ǰһ���ֵܵ�ָ���ָ��
	//��һ���ֵܵ�ָ��.
};

void Init();                           //��ʼ���ļ���
int ParseCommand();                    //����������������ֽ�ɲ�������·���ļ���
void ExecuteCommand();                 //ִ������
int cdComd();                          //����cd����
int creatComd();                       //����creat����
int delComd();                         //����del����
int dirComd();                         //����dir����
int mdComd();                          //����md����
int rdComd();
int FindPath(char *ph);                //Ѱ�Ҳ���ph��ָ���·��
int FindFilename(char Para2[]);        //�Ӳ���Para2���ҵ�Ҫ������ɾ�����ļ���Ŀ¼��������ָ��ֻ���丸�׽��
struct FileNode* CreateFileNode(char filename[],int isdir,int i_nlink);//�������
int GetInput(char* buffer,unsigned int buffer_len);//��ȡ����
int CheckCommand();//������
int GetDir(int begin,char *path,char *curDir);//��ȡ·��
void Trim(char *str);
struct FileNode *cp, *tp, *root;
char path[INPUT_LEN-COMMAND_LEN];//��¼��ǰ�߹���·��
char Para1[COMMAND_LEN],Para2[INPUT_LEN-COMMAND_LEN];
char curpath[INPUT_LEN-COMMAND_LEN],tmppath[INPUT_LEN-COMMAND_LEN];
char filename[FILENAME_LEN],tmp;
unsigned int i,j;//int i,j;

//������
int main()
{
	printf("ģ���ļ�����ϵͳ\n");
	printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
    printf("\n--------------------------------------------------------------------------------\n");
	Init();//��ʼ���ļ���
	while(1)
	{   //printf("#");
		if(ParseCommand())//�ֽ�����
			ExecuteCommand();//ִ������
	}
    return 0;
}

//ִ�������Ӻ���
void ExecuteCommand()
{
	int sign;
	//���ݲ���Para1������Ӧ�Ĺ��ܴ���ģ��
	 if(strcmp(Para1,"cd")==0)   
		 sign=cdComd(); //cd����
   else if(strcmp(Para1,"creat")==0) 
		sign=creatComd();//edit����
   else if(strcmp(Para1,"md")==0)
	   sign=mdComd();
	else if(strcmp(Para1,"del")==0) 
		sign=delComd(); //del����
	else if(strcmp(Para1,"rd")==0)
		sign=rdComd();
	else if(strcmp(Para1,"dir")==0) 
		sign=dirComd();          //dir����
	else if(strcmp(Para1,"exit")==0)
		exit(0);                         //exit����
	else
		printf("�������,������\n");  //�������벻��ȷ������
}

//�������
struct FileNode* CreateFileNode(char filename[],int isdir,int i_nlink)
{
	//������ռ�
    struct FileNode* node=(struct FileNode*)malloc(sizeof(struct FileNode));
	//��Ӧ���ݸ���ֵ
    strcpy(node->filename,filename);
	node->isdir=isdir;
	node->i_nlink=i_nlink;
	node->parent=NULL;
	node->child=NULL;
	node->sibling_prev=NULL;
	node->sibling_next=NULL;
    return node;
}

//��ʼ���ļ���
void Init()
{
	struct FileNode *dir1Node,*dir2Node,
		*file1Node,*etcNode,*libNode,*userNode,
		*binNode2,*liuNode,*sunNode,*ftiNode;
	strcpy(path,"/"); //��Ŀ¼д�뵱ǰ·��
	//�����ļ����Ľ��
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
	//�����Ӧ���ݸ�ֵ
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

//��ȡ�ļ���Ŀ¼��������ָ��ָ���丸�׽��
int FindFilename(char Para2[])
{
	i=strlen(Para2)-1;
	j=0;
	
	while(Para2[i]!='/'&& i>=0)
	{	
		filename[j]=Para2[i];
		i--; j++;
	}
	filename[j]='\0';//���������ļ���Ŀ¼��������filename��
	if(i<0) Para2[i+1]='\0';
	else Para2[i]='\0';
	j--;
	//filename��ת�������ȷ���ļ���Ŀ¼��
	for(i=0;i<strlen(filename)/2;i++,j--)
	{
		tmp=filename[i];
		filename[i]=filename[j];
		filename[j]=tmp;
	}
	//return filename[i];
	//����·��
	if(strlen(Para2)>0)
	{
		int sign=FindPath(Para2);
		if(sign==0) 
			return 0;
	}
	return 1;
}

//��������ȫ�����Ӻ���
//������볬��buffer_len�����ȡǰbuffer_len-1���ȵ����룬
//buffer_len���ַ���'/0'����
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

//�ֽ������Ӻ���
int ParseCommand()
{
	char Inputs[INPUT_LEN];
	int i=0,j=0,ch;
	unsigned int k=0;//int k=0;
	
	printf("%s>",path);
	printf("#");
	//��ȡ����
	if(GetInput(Inputs,INPUT_LEN)==-1)
	{
		printf("������̫����\n");
		return 0;
	}

	Para1[0]=Para2[0]='\0';
	//��ȡ����Para1����������
	while(Inputs[i]!=' '&&Inputs[i]!='\0' && i<COMMAND_LEN-1)
	{   
		Para1[i]=Inputs[i];
		i++;
	}//while
	Para1[i]='\0';
	
	//��������̫��
	if(i==(COMMAND_LEN-1))return 1;
	
	//��ȡ����2����·���ļ���
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
	
	//��������ȫ��ת����Сд��ĸ
	for(k=0;k<strlen(Para1);k++)
	{
		ch=tolower((int)Para1[k]);
		Para1[k]=ch;
	}
	return 1;
}
//cd���ܴ����Ӻ���
int cdComd()
{
	if(!CheckCommand()) //������
		return 0;
	if(strcmp(Para2,"..")==0)
	{   //��cd..����Ĵ���
		int i;
		while(cp->sibling_prev)
			cp=cp->sibling_prev;
		if(cp->parent)
		{ cp=cp->parent; }//�ҵ����׽��
		else
		{ return 0;  }
		//�Ե�ǰ·��������Ӧ����
		i=strlen(path);
		while(path[i]!='/'&&i>0) i--;
		if(i!=0)
			path[i]='\0';
		else
			path[i+1]='\0';
	}
	else {
		FindPath(Para2);//����·��
	}
	printf("���빤��Ŀ¼\n");
    printf("\n\nģ���ļ�����ϵͳ\n");
	printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	return 1;
}
//������Ӻ���
void Trim(char *str)
{
	int begin,end;
	char *tmp;
	begin=0;
	end=strlen(str);
	//�ҵ��ַ�����һ���ǿո��λ��
	while(str[begin]==' '&&str[begin]!='\0')
		begin++;
    //ȥ���ַ���β���ո�
    while(str[--end]==' ');
	str[end+1]='\0';
	// ��ȥ�ո�
	if(begin<end)
	{
		tmp=(char *)malloc((sizeof(char))*(end-begin+2));
		strcpy(tmp,&str[begin]);
		strcpy(str,tmp);
		free(tmp);
	}
}

//��ȡ��ǰĿ¼���Ӻ���
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

//����·������
int FindPath(char *ph)
{
	struct FileNode *temp; //struct FileNode *tp,*temp;
	char oldpath[INPUT_LEN-COMMAND_LEN];
	unsigned int i=0; //int i=0
	int sign=1;
	if(strcmp(ph,"/")==0)
	{     //ph�Ǹ�Ŀ¼
		cp=root;
		strcpy(path,"/");
		return 1;
	}
	temp=cp;
	strcpy(oldpath,path);//����ԭ·����ָ��
	if(ph[0]=='/')
	{    //ָ��ָ���Ŀ¼������
		cp=root->child;
		i++; //�˹�'/'
		strcpy(path,"/");
	}
	else {
		if(cp!=NULL&&cp!=root)
			strcat(path,"/");
		if(cp&&cp->child)
		{
			if(cp->isdir)
				cp=cp->child;//ָ��ָ��ǰĿ¼������
			else{
				printf("·������!\n");
				return 0;
			}
		}
	}
	while(i<=strlen(ph)&&cp) //��������ָ��·�����������ļ��򱨴�
	{
		int j=0;
		if(ph[i]=='/'&&cp->child)
		{
			i++; //�Թ�'/'
			if(cp->isdir)
				cp=cp->child; //���������¼�Ŀ¼
			else {
				printf("·������!\n");
				return 0;
			}
			strcat(path,"/");
		}
   // curpath ��¼��ǰҪ�ҵ�·����
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
				printf("���ļ�����Ŀ¼.\n");
				return 0;
			}
			strcat(path,cp->filename);
		}
		if(strcmp(cp->filename,curpath)!=0||cp==NULL)
		{
			strcpy(path,oldpath);
			cp=temp;
			printf("����·������\n");
			return 0;
		}
	}
	return 1;
}

//�����ļ��Ӻ���
int creatComd()
{ 
	
	struct FileNode * temp=CreateFileNode("",0,0);
	int sign;
	struct FileNode *tp;
	
	//·������Ϊ��
	if(strlen(Para2)==0)
	{
		printf("\n�����ʽ�д���.\n");
		return 0;
	}
	//���ȼ��
	if(strlen(Para2)>50)
	{
		printf("\n�ļ�������\n");
		return 0;
	}
	//��ʽ���
	if (!(isalpha(Para2[0])||Para2[0]=='_'||Para2[0]=='\0'||Para2[0]=='/'))
	{
		printf("�ļ�����ʽ�д�!\n");/* �ļ�����ĸ����Ϊ'��ĸ'��'����'��'_'��'/'��'�س�'*/
		return 0;
	}
	
	//��ȡ�ļ���
	sign=FindFilename(Para2);
	if(sign==0)
		return 0;
	
	if(cp->isdir!=1)//�統ǰָ��ָ������ļ����򱨴�
	{
		printf("you cannot edit a file in under a file!\n");
		return 0;
	}
	
	//�����ļ���㣬�����뵽ָ��Ŀ¼��
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
	   //��temp�ҵ��½����봦
	temp=temp->child;
	while(temp->sibling_next )//find the last sibing node
	{
		temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)==0&&temp->isdir==0)
		{
			printf("���ļ����Ѵ���\n");//��������
			return 0;
		}
	}//�ҵ������һ�����

	temp->sibling_next=tp;
	tp->parent=NULL;
	tp->child=NULL;
	tp->sibling_prev=temp;
	tp->sibling_next=NULL;
	
	}
	printf("�½��ļ�\n");
    printf("\n\nģ���ļ�����ϵͳ\n");
    printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	
	return 1;
}

//ɾ���ļ��Ӻ���
int delComd()
{ 
	int sign;
	struct FileNode *temp;
	//��������Ϊ��
	if(strlen(Para2)==0)
	{
		printf("\n�����ʽ�д���.\n");
		return 0;
	}
	//��ȡ�ļ���
	sign=FindFilename(Para2);
	if(sign==0) return 0;
	
	//��tempָ��Ҫɾ���Ľ��
	if(cp->child) 
	{
		temp=cp->child;
		while(temp->sibling_next && (strcmp(temp->filename,filename)!=0 || temp->isdir!=0))
			temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)!=0)
		{
			printf("�����ڸ��ļ�!\n");
			return 0;
		}
	}
	else
	{
		printf("�����ڸ��ļ�!\n");
		return 0;
	}
	//Ҫɾ���Ĳ�����Ŀ¼
	if(temp->isdir!=0)
	{
		printf("ERROR!������ֻ��ɾ���ļ�,����ɾ��Ŀ¼!\n");
		return 0;
	}
	//�������û�ʹ�ø��ļ�������ɾ��
	if(temp->i_nlink!=0)
	{
		printf("�����û������˸��ļ�,����ɾ��!\n");
		return 0;
	}
	//ɾ������
    if(temp->parent==NULL)//���ǵ�һ������
	{
		temp->sibling_prev->sibling_next=temp->sibling_next;
		if(temp->sibling_next)//���������һ���ֵܵ����
			temp->sibling_next->sibling_prev=temp->sibling_prev;
		temp->sibling_prev=temp->sibling_next=NULL;
		printf("ɾ�����");
	}//if
	else//��һ������
	{ 
		if(temp->sibling_next)//���������һ���ֵܵ����
			temp->sibling_next->parent=temp->parent;
		temp->parent->child=	temp->sibling_next;
        printf("ɾ�����\n");
	}//else
	
	free(temp);
    printf("\n\nģ���ļ�����ϵͳ\n");
	printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
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
	
	//��������Ϊ��
	if(strlen(Para2)==0)
	{
		printf("\n�����ʽ�д���.\n");
		return 0;
	}
	//���ȼ��
	if(strlen(Para2)>50)
	{
		printf("\nĿ¼������\n");
		return 0;
	}
	//��ʽ���
	if (!(isalpha(Para2[0])||Para2[0]=='_'||Para2[0]=='\0'||Para2[0]=='/'))
	{
		printf("Ŀ¼����ʽ�д�!\n");/* Ŀ¼����ĸ����Ϊ'��ĸ'��'����'��'/'*/
		return 0;
	}
	
	//��ȡĿ¼��
	sign=FindFilename(Para2);
	if(sign==0)
		return 0;
	
	if(cp->isdir!=1)//�統ǰָ��ָ������ļ����򱨴�
	{
		printf("you cannot edit a directory in under a file!\n");
		return 0;
	}
	
	//����Ŀ¼��㣬�����뵽ָ��Ŀ¼��
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
	   //��temp�ҵ��½����봦
	temp=temp->child;
	while(temp->sibling_next )//find the last sibing node
	{
		temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)==0&&temp->isdir==1)
		{
			printf("��Ŀ¼���Ѵ���\n");//��������
			return 0;
		}
	}//�ҵ������һ�����

	temp->sibling_next=tp;
	tp->parent=NULL;
	tp->child=NULL;
	tp->sibling_prev=temp;
	tp->sibling_next=NULL;
    printf("����Ŀ¼\n");
	
	}
    printf("\n\nģ���ļ�����ϵͳ\n");
    printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	
	return 1;
}
int rdComd()
{ 
	int sign;
	struct FileNode *temp;
	char cmd[2];
	//������
	if(!CheckCommand())
		return 0;

	//��ȡĿ¼��
	sign=FindFilename(Para2);
	if(sign==0) return 0;
	
	//��tempָ��Ҫɾ���Ľ��
	if(cp->child) 
	{
		temp=cp->child;
		while(temp->sibling_next && (strcmp(temp->filename,filename)!=0 || temp->isdir!=1))
			temp=temp->sibling_next;
		if(strcmp(temp->filename,filename)!=0)
		{
			printf("�����ڸ�Ŀ¼!\n");
			return 0;
		}
	}
	else
	{
		printf("�����ڸ�Ŀ¼!\n");
		return 0;
	}
	//Ҫɾ���Ĳ������ļ�
	if(temp->isdir!=1)
	{
		printf("ERROR!������ֻ��ɾ��Ŀ¼,����ɾ���ļ�!\n");
		return 0;
	}
	//�������û�ʹ�ø�Ŀ¼������ɾ��
	if(temp->child)
	{
		printf("\n��Ŀ¼��Ϊ�գ���ȷ��Ҫɾ����Y/N!\n");
	    GetInput(cmd,2);
		if(strcmp(cmd,"n")==0||strcmp(cmd,"N")==0)
			return 0;
	}
	//ɾ������
    if(temp->parent==NULL)//���ǵ�һ������
	{
		temp->sibling_prev->sibling_next=temp->sibling_next;
		if(temp->sibling_next)//���������һ���ֵܵ����
			temp->sibling_next->sibling_prev=temp->sibling_prev;
		temp->sibling_prev=temp->sibling_next=NULL;
	}//if
	else//��һ������
	{ 
		if(temp->sibling_next)//���������һ���ֵܵ����
			temp->sibling_next->parent=temp->parent;
		temp->parent->child=	temp->sibling_next;
	}//else
    printf("ɾ��Ŀ¼\n");
    printf("\n\nģ���ļ�����ϵͳ\n");
	printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	free(temp);
	
	return 1;
}


//��ʾĿ¼�Ӻ���
int dirComd()
{
	if(strlen(Para2)>0)
	{
		int sign=FindPath(Para2);//����·��
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
		return 0;//ָ��Ŀ¼Ϊ��
	}
	
	tp=cp;
	//ָ��Ŀ¼��Ϊ�գ���ʾ��������Ŀ¼���ļ���
	tp=tp->child;
	while(tp)
	{
		if(tp->isdir)
			printf("   <DIR>             %s\n",tp->filename);
		else
			printf("   <FILE>            %s\n",tp->filename);
		tp=tp->sibling_next;
	}
	printf("��ʾĿ¼\n");
    printf("\n\nģ���ļ�����ϵͳ\n");
    printf("\ncd �ı�Ŀ¼; creat �����ļ�; del ɾ���ļ�;\n");
	printf("dir ��ʾĿ¼; md ����Ŀ¼; rd ɾ��Ŀ¼; exit �˳�.\n");
	printf("\n--------------------------------------------------------------------------------\n");
	return 0;//��ӵ�
}
int CheckCommand()
{
	if(strlen(Para2)==0)
	{
		printf("�����﷨����ȷ.\n");
		return 0;
	}
	return 1;
}

