//                            _ooOoo_  
//                           o8888888o  
//                           88" . "88  
//                           (| -_- |)  
//                            O\ = /O  
//                        ____/`---'\____  
//                      .   ' \\| |// `.  
//                       / \\||| : |||// \  
//                     / _||||| -:- |||||- \  
//                     |  | | \\\ - /// | | |  
//                     | \_| ''\---/'' |_/ |  
//                      \ .-\__ `-` ___/-. /  
//                   ___`. .' /--.--\ `. . __  
//                ."" '< `.___\_<|>_/___.' >'"".  
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |  
//                 \ \ `-. \_ __\ /__ _/ .-` / /  
//         ======`-.____`-.___\_____/___.-`____.-'======  
//                            `=---='
//                          Amen������ 

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<mmsystem.h>
#include<iostream>
#pragma comment(lib,"winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
#define HEIGHT 8500
#define WIDTH 5500
#define DELINEBOOD 33
#define DELINRTIME 15
#define _CRT_SECURE_NO_DEPRECATE



typedef struct prop {  //�ýṹ��洢����͵��ߣ�����1-7Ϊ����1234567
	int x;              //xΪ����͵��ߵĺ����꣬yΪ������    
	int y;
	int have=0;  //�Ƿ�ʰȡ0����δʰȡ��������1����ʰȡ
	int food=0;//ʳ������
	int medicine=0;//ҩˮ����
	struct prop* next;
}PROP;

typedef struct nouss {  //����2���ڿ��Ƶ���ʰȡ��Ĳ���ɾ��
	int x=0;             
	int idnowHave = 0; 
	char name[10] = "0";
	int theFoodHave = 0;
	struct nouss* next;
}NO;

typedef struct number{
	int chNumber;//����ѡ��ڼ���
	int BeadNumber;//��������
	int MedNum;//ҩ����
	int FoodNum;//ʳ������
}NUM;

typedef struct location{//��ͼλ��xy
	int x = 0;
	int	y = 0;//
	int BackageX = 0;
	int BackageY = 0;
}LOC;

typedef struct active{
	int Music2;//��Ϸ�����Ƿ��
	int PhotoWalk;//�������ߵ�ͼƬ
	int NowPhoto;//��ǰ����λ��ͼƬ
}ACT;


typedef struct stone {
	int x;
	int y;
	int newx = 0;
	int newy = 0;
	int newposx=0;
	int newposy=0;
	int StoneTime = 0;
	int StoneNum = 0;
	IMAGE imgstone[2];
	IMAGE imgbobm[2];
	int stonex;
	int stoney=-250;
	int stonetime = 0;
}STONE;

void initial();
int ifMouseHit(int qie);
int ifOpenBgm(int sy);
PROP* create();//��������
void buylh();//�����軪����
void jiazaibg();//���س�ʼ��������
void bgm();//ҳ��bgm����
void bgms();//��Ϸbgm����
void newData();
void closebgm();//�ر�bgm
void choicech();//ѡ������
void qiephoto();//�л�ҳ��
void xychange();//xy����ı�
void jingdutiao(int chang);//������
int gametime(time_t t1);//ʱ��
void chushi();//��ʼ����
void thetime(int putgametime);//��Ϸʱ����ʾ
int shezhi();//���ý���
void PutProp(PROP* h);//���߱�������
void pack(PROP* h);//����
void stoneDown(int Time);
void putcharacter();//�����ж�
void failgame(int fail);//ʧ�ܽ���
void OverGame(int point);//��Ϸʤ��
PROP* putimage(PROP* h);//�ڵ�ͼ���ص���
PROP* TakeProp(PROP* h);//ʰȡ����
PROP* UseMFProp(PROP* h,int time);//ʹ��medicine��food
int UseProp(PROP* h,int Pnumber);//ʹ�õ���
void propPhoto();//�򿪱��������ѡ���͵��߽���
void FindProp(PROP* h);//Ѱ�ҵ���
void kbfree();//�ͷż�������
NO* nouse(NO*h);

NUM Number;
LOC Location;
ACT Active;
STONE Stone;
int speed,ifspeed;//�ٶȺ�ʹ�õ��ߺ��ٶ�
char shuru[10];//uid
char maxfen[5] = "0000";//��߷�
int lenght = 870;//�������ĳ���
int medthetime = 0,TIMEi=1;//ʱ�����
int IfUseProp,ifjump;//�Ƿ�ʹ�õ��ߣ���
int regame = 1,overgame = 1;//������Ϸ����//���¿�ʼ��Ϸ����
int PackPropXY[12][2] = { {160,63},{320,65},{460,63},{160,210},{310,207},{470,210},{160,350},{315,350},{470,355},{160,490},{310,490} };//�������ӵ�����
int PackPropNumber = 0;//ʰȡ���ߵ�����
time_t t1;//��ʼ��Ϸ��time
IMAGE propphoto[11],propphotobk[11];
IMAGE useprop[11];


int main()
{
	IMAGE imgnewbk, img1, img2, imgdi,imgsmalldi, imgfail, imgpack[3];
	IMAGE img111, img222, imgmedicine[3],imgfood[3];
	IMAGE imgshezhi[3], imgyinyue[3],imgfind[3], imgshezhiphoto, imghct1, imghct2;
	char fpname[64];
	
	int lenghttime = 0, timechange = 1,TheSetTime,Settime;
	int sy = 1,newbgm=0;//bgm�����ж�
	int qie = 1;//����л�ҳ��͹ر�bgm1
	int fail = 0;//ʧ�ܿ���
	int gogame = 1;//��Ϸѭ������
	int gamethetime;//��Ϸʱ��
	PROP* head;
	PROP* prophead;
	NO* nouses;

	initgraph(1200, 640, SHOWCONSOLE);
    chushi();
	loadimage(&imgdi, "photo/photo4.jpg", HEIGHT, WIDTH);
	loadimage(&imgsmalldi, "photo/smalldi.jpg", 150, 150);
	loadimage(&imgshezhi[0], "photo/shezhi.jpg", 35, 35);//����
	loadimage(&imgshezhi[1], "photo/shezhi-.jpg", 35, 35);
	loadimage(&imgshezhi[2], "photo/R.jpg", 18, 18);
	loadimage(&imgyinyue[0], "photo/shenyin.jpg", 35, 35);//����
	loadimage(&imgyinyue[1], "photo/shenyin-.jpg", 35, 35);
	loadimage(&imgyinyue[2], "photo/T.jpg", 18, 18);
	loadimage(&imgfind[0], "photo/find.jpg", 35, 35);
	loadimage(&imgfind[1], "photo/find-.jpg", 35, 35);
	loadimage(&imgfind[2], "photo/Q.jpg", 18, 18);
	loadimage(&img1, "photo/ͼ1.jpg", 135, 320);//����
	loadimage(&img2, "photo/1.jpg", 135, 320);
	loadimage(&imgpack[0], "photo/����1.jpg", 60, 60);//����
	loadimage(&imgpack[1], "photo/����2.jpg", 60, 60);
	loadimage(&imgpack[2], "photo/G.jpg", 18, 18);
	loadimage(&imghct1, "photo/hct1.jpg", 215, 290);
	loadimage(&imghct2, "photo/hct2.jpg", 215, 290);
	loadimage(&img111, "photo/111.jpg", 18, 18);
	loadimage(&img222, "photo/222.jpg", 18, 18);
	loadimage(&imgfood[0], "photo/10.jpg", 55, 55);
	loadimage(&imgfood[1], "photo/-10.jpg", 55, 55);
	loadimage(&imgfood[2], "photo/10-.jpg", 55, 55);
	loadimage(&imgmedicine[0], "photo/9.jpg", 55, 55);
	loadimage(&imgmedicine[1], "photo/-9.jpg", 55, 55);
	loadimage(&imgmedicine[2], "photo/9-.jpg", 55, 55);
	loadimage(&Stone.imgstone[0], "photo/stone1.jpg", 120, 250);
	loadimage(&Stone.imgstone[1], "photo/stone2.jpg", 120, 250);
	loadimage(&Stone.imgbobm[0], "photo/bobm1.jpg", 160, 160);
	loadimage(&Stone.imgbobm[1], "photo/bobm2.jpg", 160, 160);
	loadimage(&imgnewbk, "photo/photo2.jpg", 1200, 640);
	mciSendString("close BGM/hailang.mp3", 0, 0, 0);
	mciSendString("open BGM/amsg.mp3", 0, 0, 0);
	mciSendString("play BGM/amsg.mp3 repeat", 0, 0, 0);
	putimage(0, 0, &imgnewbk);
    InputBox(shuru, 100, "������UID����1-8λ����,��ĸ���֣�");
	while(1)
	{
		if ( strlen(shuru)==0 || shuru[0] == ' '|| shuru[0] == '.'||shuru[0] == ','||shuru[0] == '/') {
			InputBox(shuru, 100, "��Ч���룡����������UID����1-8λ����,��ĸ���֣�");
		}
		else{
			break;
		}
	}

		buylh();

		srand((unsigned)time(NULL));
	//����ҳ��
    while(1){
		cleardevice();
		if (newbgm > 0)
		{
			mciSendString("open BGM/amsg.mp3", 0, 0, 0);
			mciSendString("play BGM/amsg.mp3 repeat", 0, 0, 0);
		}
		newbgm++;
		sprintf_s(fpname, "data/%s", shuru);
		FILE* fp = fopen(fpname, "r");
		if (fp) {
			fscanf(fp, "%s", &maxfen);
			fclose(fp);
		}
		else
		{
			FILE* fpp = fopen(fpname, "w");
			fclose(fpp);
		}
		loadimage(&imgnewbk, "photo/photo2.jpg", 1200, 640);
		//initgraph(1200, 640, SHOWCONSOLE);
		BeginBatchDraw();
		putimage(0, 0, &imgnewbk);
		FlushBatchDraw();
		

	    jiazaibg();
	
         //�ж��л�ҳ���bgm����
	     qie = 1;
	    while (qie) {
			qie=ifMouseHit(qie);
			sy = ifOpenBgm(sy);
		   
	     }
	     IMAGE chushid;

         overgame = 1;
		// if (kbhit) {
		BeginBatchDraw();
		
		  while (overgame) {
				 // qiephoto();
			  //initialdata();
			  head = create();
			  propPhoto();
			  fail = 0;
			  timechange = 1;
			  TheSetTime = 0;
			  Settime = 0;
			  newData();
			 while(regame){//zhu xun huan

				 cleardevice();

				 //������Ϸ����
				 Location.BackageX = -HEIGHT/2 - Location.x+600;
				 Location.BackageY = -WIDTH/2 + Location.y+540;
				 putimage(Location.BackageX,Location.BackageY, &imgdi);
				 //���ƺϳ�̨
				 putimage(105 - Location.x, 255 + Location.y, &imghct2, SRCAND);
				 putimage(105 - Location.x, 255 + Location.y, &imghct1, SRCPAINT);
				 
				 gamethetime = gametime(t1);
				 lenghttime = gamethetime;
				 if(timechange==0){nouses=nouse(nouses);}
				 stoneDown(gamethetime);
				 //���Ƶ���
				  prophead = putimage(head);
				 prophead = TakeProp(prophead);
				 prophead = UseMFProp(prophead,gamethetime);
				 //Ѱ��ͼ��
				 putimage(1050, 15, &imgfind[0], SRCAND);
				 putimage(1050, 15, &imgfind[1], SRCPAINT);
				 putimage(1060, 55, &imgfind[2]);
				 //����ͼ��
				 putimage(1100, 15, &imgshezhi[0], SRCAND);
				 putimage(1100, 15, &imgshezhi[1], SRCPAINT);
				 putimage(1110, 55, &imgshezhi[2]);
				 //����ͼ��
				 putimage(1150, 15, &imgyinyue[0], SRCAND);
				 putimage(1150, 15, &imgyinyue[1], SRCPAINT);
				 putimage(1160, 55, &imgyinyue[2]);


				 //���Ʊ���
				 putimage(15, 550, &imgpack[1], SRCAND);
				 putimage(15, 550, &imgpack[0], SRCPAINT);
				 putimage(73, 605, &imgpack[2]);
				 //ҩˮͼ��
				 if (Number.MedNum == 0)
				 {
					 putimage(1120, 110, &imgmedicine[1], SRCAND);
					 putimage(1120, 110, &imgmedicine[2], SRCPAINT);
				 }
				 else
				 {
					 putimage(1120, 110, &imgmedicine[1], SRCAND);
					 putimage(1120, 110, &imgmedicine[0], SRCPAINT);
				 }
				 //ʳ��ͼ��
				 if (Number.FoodNum == 0) {
					 putimage(1120, 169, &imgfood[1], SRCAND);
					 putimage(1120, 169, &imgfood[2], SRCPAINT);
				 }
				 else
				 {
					 putimage(1120, 169, &imgfood[1], SRCAND);
					 putimage(1120, 169, &imgfood[0], SRCPAINT);
				 }
				 //ҩˮ��ʳ���1��2��ʾ
				 putimage(1169, 144, &img111);
				 putimage(1169, 205, &img222);

				 //����uid
				 outtextxy(965, 555, "UID:");
				 outtextxy(1044, 555, shuru);
				 //����С��ͼ
				 setlinecolor(WHITE); //���ÿ���ɫ
				 setlinestyle(PS_SOLID, 2);
				 rectangle(5, 5, 159, 159);
				 putimage(7, 7, &imgsmalldi);//С��ͼͼƬ
				 setfillcolor(RGB(115,253,255));
				 if(77+Location.x / 39>=7&& 81 - Location.y / 28>=7&&77+Location.x / 39<=157&& 81 - Location.y / 28<=157){//��С��ͼ��Χ�ڼ�������λ��
				     solidcircle(77 + Location.x/39, 81 - Location.y/28, 3);//����λ��
				 }
				 //��������ʱ�����
				 if (lenghttime- Settime >= DELINRTIME*timechange)
				 {
					 lenght = lenght -DELINEBOOD;
					 lenghttime = 0;
					 timechange++;
				 }
			 //��Ϸʱ��
				 
				 Settime += TheSetTime;
				 thetime(gamethetime- Settime);
				 //������
				 jingdutiao(gamethetime - Settime);
				 putcharacter();
				 xychange();
				 if (ifspeed == 1)
				 {
					 //Sleep(4200);
				   system("pause");
					 ifspeed++;
				 }
			// 
			 OverGame(gamethetime - Settime);
			 //��Ϸ�����ж�
			 if (lenght <= 325)
			 {
				 regame = 0;
				 fail = 1;
				 mciSendString("open BGM/ʧ��.wav", 0, 0, 0);
				 mciSendString("play BGM/ʧ��.wav", 0, 0, 0);
			 }

			 FlushBatchDraw();
			//ʧ�ܽ���
			 failgame(fail);
			 //��qѰ��
			 if (GetAsyncKeyState('Q'))
			 {
				 FindProp(prophead);
			 }
			 TheSetTime = shezhi();//����
			 pack(prophead);
			 kbfree();//�ͷŰ���
			}	
	      }

	}


	//getchar();
	closegraph();
	return 0;
}


//�Զ��庯������
int ifMouseHit(int qie) {
	if (MouseHit())
	{

		MOUSEMSG msg = GetMouseMsg();

		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (msg.x > 500 && msg.x < 680 && msg.y>540 && msg.y < 590)
			{
				qiephoto();//�л�ҳ��
				qie = 0;
			}
			break;
		}
	}
	return qie;
}

int ifOpenBgm(int sy) {
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			
			//bgm����
			if (msg.x > 1110 && msg.x < 1180 && msg.y>25 && msg.y < 80)
			{
				if (sy == 1) {
					mciSendString("close BGM/amsg.mp3", 0, 0, 0);
					sy = 0;
				}
				else {
					mciSendString("play BGM/amsg.mp3", 0, 0, 0);
					sy = 1;
				}
			}
			break;
		}
	}
	return sy;
}

void buylh()
{
	IMAGE imgbuylh;
	MOUSEMSG msg;
	int gobuy;
	loadimage(&imgbuylh, "photo/buylh.jpg", 900, 504);
	
	BeginBatchDraw();
	putimage(150,68, &imgbuylh);
	mciSendString("open BGM/lxz.mp3", 0, 0, 0);
	mciSendString("play BGM/lxz.mp3", 0, 0, 0);
	FlushBatchDraw();
	gobuy = 1;
    while (gobuy) {
		if (MouseHit())
		{
			msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 967 && msg.x < 1040 && msg.y>315 && msg.y < 506)
				{
					printf("   dddd     ");
					gobuy = 0;
					mciSendString("open BGM/buylhbgm.mp3", 0, 0, 0);
					mciSendString("play BGM/buylhbgm.mp3", 0, 0, 0);
					Sleep(800);
				}
			}
		}
	}
}


void jiazaibg() {
	IMAGE img123;
	loadimage(&img123, "photo/photo2.jpg", 1200, 640);
	printf("12345679");
	BeginBatchDraw();
	putimage(0, 0, &img123);
	//void jingdutiao();
	//bgm();

	//������߷�
	settextcolor(RED);
	settextstyle(45, 0, 0);
	setbkmode(TRANSPARENT);
	outtextxy(150, 50, "��߷֣�");
	outtextxy(285, 50, maxfen);

	settextcolor(WHITE);
	outtextxy(1044, 555, shuru);
	FlushBatchDraw();
}



void chushi()//���س�ʼ����
{
	IMAGE chushi[9],imgchushi;
	IMAGE jiazai[8],imgjiazai;
	char arry[64];
	char name[64];
    printf("1111");
	mciSendString("open BGM/hailang.mp3", 0, 0, 0);//��������
	
	int i = 0;
	
	loadimage(&imgjiazai, "photo/jiazai/9.jpg", 1200, 640);

    mciSendString("play BGM/hailang.mp3 repeat", 0, 0, 0);
	for ( i = 0; i < 9;i++)//����ͼƬ
	{	
		sprintf_s(arry,"photo/chushi%d.jpg",i+1);
		loadimage(&chushi[i],arry,1200,640);
		
	}
	for (i = 0; i < 7; i++)//û��1900s�л�1��ͼƬ
	{
		putimage(0, 0, &chushi[i]);
		Sleep(1900);
	}
	putimage(0, 0, &chushi[7]);
    system("pause");
	putimage(0, 0, &chushi[8]);
	system("pause");


	for (i = 0; i < 8; i++)
	{
		sprintf_s(name, "photo/jiazai/%d.jpg", i + 1);
		loadimage(&jiazai[i], name, 1200, 640);

	}
	for (i = 0; i < 8; i++)
	{
		putimage(0, 0, &jiazai[i]);
		Sleep(1700);
	}
	Sleep(2100);
	putimage(0, 0, &imgjiazai);
}

void initialdata() {
	
}

void bgm()//�������ֿ���
{
	mciSendString("open BGM/����bgm.mp3", 0, 0, 0);
	mciSendString("play BGM/����bgm.mp3 repeat", 0, 0, 0);
}



void closebgm() {//�������ֿ���
	int sy = 1;
	if (sy == 1) {
		mciSendString("close BGM/����bgm.mp3", 0, 0, 0);
		sy = 0;
	}
	else {
		mciSendString("play BGM/����bgm.mp3", 0, 0, 0);
		sy = 1;
	}
}




void bgms()
{
	mciSendString("open BGM/bgm2.mp3", 0, 0, 0);
	mciSendString("play BGM/bgm2.mp3 repeat", 0, 0, 0);
}

void newData() {//��ʼ������
	
	Number.BeadNumber = 0;
	TIMEi = 1;
	speed = 35;
	t1 = time(NULL);
	regame = 1;
	lenght = 870;
	Stone.StoneTime = 0;
	Stone.StoneNum = 0;
	medthetime = 0;
	Location.x = 0;
	Location.y = 0;
	Number.MedNum = 0;
	Number.FoodNum = 0;
	Active.NowPhoto = 0;
	
}

//�л�ҳ��
void qiephoto() {
	IMAGE img,src,img1,img2,imgchinteroduce,imgpack1,imgpack2,imglh1,imglh2;
	int chinteroduce;
	chinteroduce = 1;
	mciSendString("close BGM/amsg.mp3", 0, 0, 0);
    loadimage(&img, "photo/photo4.jpg", HEIGHT, WIDTH);
	loadimage(&img1, "photo/ͼ1.jpg", 143, 320);
	loadimage(&img2, "photo/1.jpg", 143, 320);
    loadimage(&imglh1, "photo/lh1.jpg", 150, 320);
	loadimage(&imglh2, "photo/lh2.jpg", 150, 320);
	loadimage(&imgpack1, "photo/����1.jpg", 60, 60);
	loadimage(&imgpack2, "photo/����2.jpg", 60, 60);

    putimage(-HEIGHT/2+600,-WIDTH/2+540, &img);
    choicech();
	
	BeginBatchDraw();
	cleardevice();
	
	putimage(-HEIGHT/2+600, -WIDTH/2+540, &img);

   
	putimage(15, 550, &imgpack2, SRCAND);
	putimage(15, 550, &imgpack1, SRCPAINT);

	outtextxy(965, 555, "UID:");
	outtextxy(1044, 555, shuru);

	
	bgms();

	if (Number.chNumber == 1)
	{
		putimage(540, 200, &img1, SRCAND);
		putimage(540, 200, &img2, SRCPAINT);
	}
	if (Number.chNumber ==2)
	{
		putimage(540, 200, &imglh2, SRCAND);
		putimage(540, 200, &imglh1, SRCPAINT);
	}
	outtextxy(480,300,"��׼����ʼ��Ϸ");

	
		if (Number.chNumber == 1)
	    {
			mciSendString("close BGM/characterbgm.mp3", 0, 0, 0);
		mciSendString("open BGM/characterbgm.mp3", 0, 0, 0);
		mciSendString("play BGM/characterbgm.mp3", 0, 0, 0);
	    }
		if (Number.chNumber ==2)
		{
			mciSendString("close BGM/lh.mp3", 0, 0, 0);
			mciSendString("open BGM/lh.mp3", 0, 0, 0);
			mciSendString("play BGM/lh.mp3", 0, 0, 0);
		}


	FlushBatchDraw();
	//system("pause");

}


//ѡ������
void choicech() {
	int chinteroduce, i,j=1;
	IMAGE imgchinteroduce[2];
	char arry[64];
	chinteroduce = 1;
	i = 1;
	for (i = 0; i < 2; i++)
	{
		sprintf_s(arry, "./character/choicech/%d.jpg", i+1 );
		loadimage(&imgchinteroduce[i], arry, 1000, 500);

	}
	
	j = 0;
	while (chinteroduce)
	{
		BeginBatchDraw();
		putimage(100, 70, &imgchinteroduce[j]);
		FlushBatchDraw();
		Sleep(500);
		
		
		if (GetAsyncKeyState('A'))//a����
		{
			j--;
		}

		if (GetAsyncKeyState('D'))//d����
		{
			j++;
		}

		if (j < 0)
		{
			j = j + 2;
		}

		if (j >1)
		{
			j = j - 2;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			chinteroduce = 0;
			Number.chNumber = j+1;
		}
	}
}


//xy��ͼλ�øı�
void xychange() {

	if ((Location.BackageX-speed) > -HEIGHT +1300 && (Location.BackageX +speed)<-500 && (Location.BackageY-speed) > -WIDTH + 650 &&(Location.BackageY +speed)< -200)
	{
	     if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	     {
			 Location.y = Location.y + speed;//��
			 ifspeed = 0;
	      }
	     if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	      {
			 Location.y = Location.y - speed;//��
			  ifspeed = 0;
	        }
	     if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	     {
			 Location.x = Location.x - speed;//��
				ifspeed = 0;
	      }
	     if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	     {
			 Location.x = Location.x + speed;//��
				ifspeed = 0;
	     }
    }
	else 
	{
		
		if (Active.NowPhoto == 1)
		{
			//printf("                       %d \n",y);
			//printf("%d  1   ",tp);
			Location.y = Location.y- 50;
			mciSendString("close BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("open BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("play BGM/qmdqy.mp3", 0, 0, 0);
			ifspeed ++;
			//printf("                       %d \n", y);
		}
		if (Active.NowPhoto == 0)
		{
			Location.y = Location.y + 50;
			//printf("%d  0   ", tp);
			mciSendString("close BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("open BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("play BGM/qmdqy.mp3", 0, 0, 0);
			ifspeed ++;
		}
		if (Active.NowPhoto == 2)
		{
			Location.x = Location.x + 50;
			//printf("%d  2   ", tp);
			mciSendString("close BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("open BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("play BGM/qmdqy.mp3", 0, 0, 0);
			ifspeed ++;
		}
		if (Active.NowPhoto == 3)
		{
			Location.x = Location.x - 50;
			//printf("%d   3  ", tp);
			mciSendString("close BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("open BGM/qmdqy.mp3", 0, 0, 0);
			mciSendString("play BGM/qmdqy.mp3", 0, 0, 0);
			ifspeed++;
		}

	}

}

//��Ϸʱ�����
int gametime(time_t t1)
{
	time_t t2;
	int interval;
	t2 = time(NULL);
	interval = t2 - t1;

	return interval;

}


//��Ϸʱ����ʾ
void thetime(int putgametime) {
	char fen[20] = "0";
	char miao[20]="0";
	int thefen=0;
	int themiao=0;
	
	themiao = putgametime;
	if (themiao >= 60*TIMEi)//�����60��=0����++
	{

		thefen=thefen+1;
		//
		TIMEi++;
	}
    //ʱ��������ӡ
	sprintf_s(fen, "%2d",TIMEi-1 );//intתchar
	sprintf_s(miao, "%2d", themiao-60*(TIMEi - 1));
	outtextxy(547, 20, "0");
	outtextxy(557,20,fen);//��
	outtextxy(585, 17, ":");
	outtextxy(594, 20, miao);//��
}




//������
void jingdutiao(int chang)
{

	setfillcolor(GREEN);  //���ý����������ɫ
	setlinecolor(WHITE); //���ý���������ɫ
	setlinestyle(PS_SOLID, 1);//��������
	rectangle(324,569,871,586);//��������λ��
	if(lenght>325)
	   bar(325,570,lenght,585);//��������
}



void stoneDown(int Time) {
	int i;
	if (Time - Stone.StoneTime <10) {//ÿ10sһ��ѭ��
	  
	    if(Stone.StoneNum==0)
	    { 
			i= rand() % 520;
            Stone.newy = rand() % 520;//�������ʯͷxy����
			Stone.newx = rand() % 1000;		
			Stone.StoneNum++;//ֻ����һ��
		}
		Stone.x = 50+Stone.newx- Location.x+Stone.newposx;//ʯͷ����Ļ�˶�
		Stone.y = 50 +Stone.newy + Location.y-Stone.newposy;
		if (Time >= Stone.StoneTime && Time < Stone.StoneTime + 3)//0-3s��ɫ��ʾȦ
		{
			setfillcolor(RED);//��ɫ
			setlinecolor(RED); //���ÿ���ɫ
			setlinestyle(PS_SOLID, 12);
			circle(Stone.x, Stone.y, 70);//Բ��
			fillcircle(Stone.x, Stone.y, 20);//����Բ
			Stone.stoney = -250;//�ʼ��ʯ����Ļ��
			mciSendString("close BGM/boinbgm.mp3", 0, 0, 0);
			Stone.stonetime = 0;//��¼��Ѫ����ÿѭ��һ�ξ͹��㣬ֻ��=0ʱ��Ѫ��֮��ͼ�1
		}
		else if (Time >= Stone.StoneTime + 3 && Stone.stoney + 220 < Stone.y && Stone.stonetime == 0)
		{
			putimage(Stone.x - 60, Stone.stoney, &Stone.imgstone[1], SRCAND);//������ʯ
			putimage(Stone.x - 60, Stone.stoney, &Stone.imgstone[0], SRCPAINT);
			if (GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState('S'))//��ʯ�½��ٶ�
			{
				Stone.stoney += 89;
			}
			else if (GetAsyncKeyState('W')) {//�ٶ�
				Stone.stoney += 120;
			}
			else {//�ٶ�
				Stone.stoney += 39;
			}


		}
		else if (Time <= Stone.StoneTime + 5)//��ʯ���µ�5s���ر�ը����������
		{
			if (Stone.stonetime == 1 && Stone.x - 70 > 480 && Stone.x - 70 < 620 && Stone.y - 70 > 340 && Stone.y - 70 < 470) {//�б��Ƿ��Ѫ
				lenght = lenght - 45;//Ѫ������
			}
			//printf("          %d    \n", Time - Stone.StoneTime);
			mciSendString("open BGM/boinbgm.mp3", 0, 0, 0);//����
			mciSendString("play BGM/boinbgm.mp3", 0, 0, 0);
			Stone.stonetime++;//ֻ��һ��Ѫ
			putimage(Stone.x - 80, Stone.y - 80, &Stone.imgbobm[1], SRCAND);//��ըͼƬ
			putimage(Stone.x - 80, Stone.y - 80, &Stone.imgbobm[0], SRCPAINT);

		}
		else
			printf("1");
    }
	else
	{
		Stone.StoneTime = Time;//10s������ò���
		Stone.StoneNum = 0;
		Stone.newposx = Location.x;
		Stone.newposy = Location.y;
	}

}


//����
int shezhi() {
	time_t settime = time(NULL);
	IMAGE imgshezhiphoto;
	int gogame=1;
	if (GetAsyncKeyState('R'))//r����
	{
		gogame = 1;
		loadimage(&imgshezhiphoto, "photo/shezhiphoto.jpg", 800, 500);
        mciSendString("open BGM/shezhibgm.wav", 0, 0, 0);
		mciSendString("play BGM/shezhibgm.wav", 0, 0, 0);
		while (gogame) {
			// printf("����λ��%d   %d\n ", msg1.x, msg1.y);
			
			BeginBatchDraw();
			putimage(200, 80, &imgshezhiphoto);
			FlushBatchDraw();
            system("pause");
			//c����
			if (GetAsyncKeyState('C'))//c������Ϸ
			{
				gogame = 0;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
				break;
			}
			//x���¿�ʼ
			if (GetAsyncKeyState('X'))
			{
				gogame = 0;
				regame = 0;
				Location.x = 0;
				Location.y = 0;
				lenght = 870;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
				break;
			}

			if (GetAsyncKeyState('Z'))//z������
			{
                cleardevice();
                overgame = 0;
                regame = 0;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
				mciSendString("close BGM/bgm2.mp3", 0, 0, 0);
				mciSendString("close BGM/characterbgm.mp3", 0, 0, 0);
                break;
				system("pause");

			}
		} 
	}



	if (GetAsyncKeyState('T'))//t����
	{
		Sleep(200);
		if (Active.Music2 == 1) {
			mciSendString("close BGM/bgm2.mp3", 0, 0, 0);
			Active.Music2 = 0;
		}
		else {
			mciSendString("play BGM/bgm2.mp3", 0, 0, 0);
			Active.Music2 = 1;
		}
	}
	time_t settime1 = time(NULL);
	return settime1- settime;
}

void pack(PROP* h)//����
{
	IMAGE imgpackbg;
	int gogame = 1;
	int Pnumber;
	Pnumber = 0;
	if (GetAsyncKeyState('G'))//G�򿪱���
	{
		Sleep(200);
		gogame = 1;
		loadimage(&imgpackbg, "photo/packbg.jpg", 1000, 600);
		mciSendString("open BGM/shezhibgm.wav", 0, 0, 0);
		mciSendString("play BGM/shezhibgm.wav", 0, 0, 0);
		IfUseProp = 0;
		while (gogame) {//ѭ�����ؽ���
			BeginBatchDraw();
			putimage(100, 20, &imgpackbg);
			PutProp(h);
			Pnumber=UseProp(h,Pnumber);
			FlushBatchDraw();
			Sleep(300);
			//c����
			if (GetAsyncKeyState('X'))
			{
				gogame = 0;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
			}
		}

	}
}


PROP* UseMFProp(PROP* h,int time) {//ʹ�õ���
	PROP* r, * p;
	p = h;
	int i = 0;

	if (time - medthetime > 20)
	{
		speed = 35;
	}
	if (GetAsyncKeyState('1')&&Number.MedNum!=0)//��1 ��ʹ��ҩˮ  ����Ʒ������Ϊ0
	{
		Sleep(100);
		for (i = 0; i < 11; i++)//��������Ѱ�ҵ��߲������߱��Ϊ��ʹ��
		{
			if (p->medicine == 1)//��Ϸ�ٶ�����
			{
				p->have = 2;
				p->medicine = 2;
				Number.MedNum--;
				medthetime = time;
				speed = 55;
				break;
			}
			r = p;
			p = p->next;
		}
	}
	
	if (GetAsyncKeyState('2') && Number.FoodNum != 0)//��2 ʹ��ʳ��
	{
		Sleep(100);
		for (i = 0; i < 11; i++)//ͬ��
		{
			if (p->food == 1)
			{
				p->have = 2;
				p->food = 2;
				Number.FoodNum--;
				lenght = lenght + 100;
				if (lenght > 870)//������������
				{
					lenght = 870;
				}
				break;
			}
			r = p;
			p = p->next;
		}
	}
	return h;

}



int UseProp(PROP* h,int Pnumber) {//�򿪱��������ѡ���͵��߽���

	PROP * p;
	p = h;
	int i = 0;
	char name[64];
	IfUseProp = 0;
	mciSendString("close BGM/chakprop.mp3", 0, 0, 0);
	mciSendString("open BGM/chakprop.mp3", 0, 0, 0);
	
	for (i = 0; i < 11; i++)
	{

		if (p->have == 1)//���ص��߽���ͼƬ
		{
			sprintf_s(name, "photo/propuse/%d.jpg", i + 1);
			loadimage(&useprop[IfUseProp], name, 475, 455);
			IfUseProp++;
		}

		p = p->next;
	}
	
	for (i = IfUseProp; i < 11; i++)//���ؿհ׽���bk
	{
		loadimage(&useprop[i], "photo/propuse/12.jpg", 475, 455);
	}
	//ѡ���
	putimage(590,127, &useprop[Pnumber]);
	setlinecolor(RED); //���ý���������ɫ
	setlinestyle(PS_SOLID, 5);
	rectangle(PackPropXY[Pnumber][0]-15, PackPropXY[Pnumber][1]-15, PackPropXY[Pnumber][0]+93, PackPropXY[Pnumber][1]+93);
	//ѡ������ƶ�
	if (GetAsyncKeyState('W'))//w����
	{
		if (Pnumber > 2&& Pnumber<11) {
			Pnumber = Pnumber - 3;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);

		}
	}
	if (GetAsyncKeyState('S'))//s����
	{
		if (Pnumber <8 ) {
			Pnumber = Pnumber + 3;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);

		}
	}
	if (GetAsyncKeyState('A'))//a����
	{
		if(Pnumber >0 && Pnumber <11){
			Pnumber--;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);
         }
	}
	if (GetAsyncKeyState('D'))//������
	{
		if(Pnumber <10 ){
			Pnumber++;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);
         }
	}
	printf("        PNUMBER++====    %d",Pnumber);
	Sleep(100);
	return Pnumber;
}



//������
PROP* create()
{
	PROP* p, * check = NULL, *r = NULL, * head = NULL;
	int i,j=0,n=1;
	int xx = 0;
	int yy = 0;
	int ifmax;//�ж���/����ƽ���Ƿ����1000000
	p = head;
    srand((unsigned)time(NULL));
	for (i = 0; i < 11; i++)
	{
		while(1){
		     p = (PROP*)malloc(sizeof(PROP));//��̬��������
			if (p != NULL)
			{
				break;
			}
		}
		while(1)
		{
			ifmax = 0;
			check = head;
			p->x = rand() % (HEIGHT - 3000) + 1400;//�����������
			p->y = rand() % (WIDTH - 2200) + 1100;//y������
			for (j = 0; j < i; j++)
			{
				//�жϾ����С
				if ((p->x - check->x) * (p->x - check->x) + (p->y - check->y) * (p->y - check->y) > 360000)
				{
					ifmax++;
				}
				check = check->next;

			}
			if (ifmax == j)//�ж��Ƿ񶼷�������
			{
				break;
			}
			
		}

			p->have = 0;//have����ʰȡ  ��ʼΪ0��ʾȫ��δʰȡ
			p->medicine = 0;//ҩƷ������¼
			p->food = 0;//ʳ��������¼

			p->next = NULL;
			if (head == NULL)
			{
				head = p;
				r = p;
			}
			else {
				r->next = p;
				r = p;
			}
	}
	return head;
}


//�������ͼƬ
void propPhoto()
{
	char Pname[64];
	char Parry[64];
	int i;
	//���ص���ͼƬ
	for(i=0;i<11;i++){
	sprintf_s(Pname, "photo/prop/%d.jpg", i+1);
	sprintf_s(Parry, "photo/prop/-%d.jpg", i+1);
	loadimage(&propphoto[i], Pname, 80, 80);
	loadimage(&propphotobk[i], Parry, 80, 80);
	}
}

NO* nouse(NO*h) {//���������ɾ�������
	NO* p, * r;
	h->x = 0;
	while (h != NULL)
	{
		h->idnowHave = 0;
		h->theFoodHave = 0;
		p = h;
		r = p->next;
		while (r != NULL) {
			if (r->x != h->x)//����������ߵ������겻��ͬ�����һ����������
			{
				r = r->next;
				NO* newp = (NO*)malloc(sizeof(NO));
				newp->idnowHave= 1;
				newp->theFoodHave = 0;
				newp->next = r->next;
				r->next = newp;
				p = p->next;
				h->idnowHave = h->theFoodHave = 0;
			}
			else//�����ɾ������һ������ʾ
			{
				p->next = r->next;
				free(r);
				r = p->next;
				h->theFoodHave++;
				setlinecolor(WHITE);
				setlinestyle(PS_SOLID, 3);
				rectangle(-656, -240, -763, -290);
				outtextxy(-660, -245, "have the food");
			}


		}

		h = h->next;
	}
	return h;
}



//�����δʰȡ���ڵ�ͼ�ϼ��ص���ͼƬ
PROP* putimage(PROP* h) {

	PROP* r, * p;
	p = h;
	int i = 0;
	for (i = 0; i < 11; i++)
	{

		if (p->have == 0)
		{
			putimage(p->x+Location.BackageX,p->y+ Location.BackageY , &propphotobk[i], SRCAND);
			putimage(p->x+ Location.BackageX,p->y+ Location.BackageY , &propphoto[i], SRCPAINT);
		}
		r = p;
		p = p->next;
	}
	return h;
}


//ʰȡ����
PROP* TakeProp(PROP* h) {

	PROP* r, * p;
	p = h;
	int i = 0;
	for (i = 0; i < 11; i++)
	{
       //�ж��Ƿ��ڿ�ʰȡ�ķ�Χ��
		if (p->have ==0&& p->x + Location.BackageX<=630 && p->x + Location.BackageX >= 530 && p->y + Location.BackageY<= 450 && p->y + Location.BackageY >= 250)
		{
		//	printf("λ��������\n");
			setlinecolor(WHITE);
			setlinestyle(PS_SOLID, 3);
			rectangle(656,240,763,290); 
			outtextxy(660,245,"Fʰȡ");
			//�����f��ʰȡ
			if (GetAsyncKeyState('F'))
			{
				p->have = 1;//ʰȡ����have=1���Ͳ��ڵ�ͼ�ϼ�����

				if (i == 7 || i ==8)
				{
					p->medicine = 1;//�����ҩ�ͱ��һ��   foodͬ��
					Number.MedNum++;
				}

				if (i == 9|| i == 10)
				{
					p->food = 1;
					Number.FoodNum++;//ʳ������һ
				}

				mciSendString("close BGM/takeprop.mp3", 0, 0, 0);
				mciSendString("open BGM/takeprop.mp3", 0, 0, 0);
				mciSendString("play BGM/takeprop.mp3", 0, 0, 0);
				if (i<7)//���������+1
				{
					Number.BeadNumber++;
				}
				
			}

		}

		//
		r = p;
		p = p->next;
	}


	return h;
}



//�������ص���
void PutProp(PROP* h) {

	PROP* r, * p;
	p = h;
	r = h;
	int i = 0;
	PackPropNumber = 0;
	for (i = 0; i < 11; i++)
	{
		
		if (p->have == 1)//���have��1�ͼ��ص���
		{
			printf("\n%d          %d\n",i,p->have );//����ͼƬ
			putimage(PackPropXY[PackPropNumber][0], PackPropXY[PackPropNumber][1], &propphotobk[i], SRCAND);
			putimage(PackPropXY[PackPropNumber][0], PackPropXY[PackPropNumber][1], &propphoto[i], SRCPAINT);
			PackPropNumber++;
		}

		p = p->next;
	}

}



//Ѱ�ҵ���
void FindProp(PROP* h) {

	PROP * p;
	p = h;
	int i = 0;
	int theX=0, theY=0;
	setlinecolor(WHITE);//����ֱ�߸�ʽ
	setlinestyle(PS_DASH,8);

	for (i = 0; i < 11; i++)
	{
		
		if (p->have == 0)
		{
			//������ǰ���Ѱ��
			BeginBatchDraw();
			theX = (p->x + Location.BackageX - 605) / 20;//����ֻ�����20��
			theY= (p->y + Location.BackageY - 505) / 20;
			line(605,505,theX+605,theY+505);
			FlushBatchDraw();
			Sleep(500);//�ӳ�500s
			break;
		}

		p = p->next;
	}

}


//�ͷ�δ����ļ�λ
void kbfree() {
	if (GetAsyncKeyState('F'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('R'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('X'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('C'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('T'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('A'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('W'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('S'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('D'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState('Z'))
	{
		printf(" ");
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		printf(" ");
	}
	if (MouseHit)
	{
		printf(" ");
	}
}




//�����ж�
void putcharacter() {

	IMAGE character[4][5];
	IMAGE characterbk[4][5];
	char name[64];
	char namebk[64];
	int i, j;
	if (Active.PhotoWalk >= 4)
	{
		Active.PhotoWalk = Active.PhotoWalk - 4;//һֱ��1-4ѭ��
	}
	
	//����ͼƬ
	
	for (i = 0; i < 4; i++)//���ر���ͼ
	{
		for(j=0;j<5;j++)
		{
			sprintf_s(name, "character/%d/%d/%d.jpg", Number.chNumber,i + 1,j+1);
			loadimage(&character[i][j], name, 143, 320);
		}
	}

	for (i = 0; i < 4; i++)//��������ͼ
	{
		for (j = 0; j < 5; j++)
		{
			sprintf_s(namebk, "character/%d/%d/-%d.jpg", Number.chNumber,i + 1,j+1);
			loadimage(&characterbk[i][j], namebk, 143,320);
		}
	}

	
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//wsad��������
	{
		putimage(540, 200, &characterbk[1][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[1][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))//wsad��������
	{
		putimage(540, 200, &characterbk[0][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[0][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))//wsad��������
	{
		putimage(540, 200, &characterbk[2][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[2][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 2;
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))//wsad��������
	{
		putimage(540, 200, &characterbk[3][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[3][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 3;
	}
	//jump
	/*else if (GetAsyncKeyState(VK_SPACE) && Active.NowPhoto == 1)
	{
		putimage(540, 120, &characterbk[1][4], SRCAND);
		putimage(540, 120, &character[1][4], SRCPAINT);
		ifjump = 1;

	}

	else if (GetAsyncKeyState(VK_SPACE) && Active.NowPhoto == 0)
	{
		putimage(540, 120, &characterbk[0][4], SRCAND);
		putimage(540, 120, &character[0][4], SRCPAINT);
		ifjump = 1;
	}

	else if (GetAsyncKeyState(VK_SPACE) && Active.NowPhoto == 2)
	{
		putimage(500, 120, &characterbk[2][4], SRCAND);
		putimage(500, 120, &character[2][4], SRCPAINT);
		ifjump = 1;
	}
	else if (GetAsyncKeyState(VK_SPACE) && Active.NowPhoto == 3)
	{
		
		putimage(540, 120, &characterbk[3][4], SRCAND);
		putimage(540, 120, &character[3][4], SRCPAINT);
		ifjump = 1;
	}*/
	else if (ifjump == 1)
	{
		putimage(540, 200, &characterbk[Active.NowPhoto][0], SRCAND);
		putimage(540, 200, &character[Active.NowPhoto][0], SRCPAINT);
		Sleep(300);
		ifjump = 0;
	}

	else {//δ�ƶ�ʱ�Ľ���
		putimage(540, 200, &characterbk[Active.NowPhoto][0], SRCAND);
		putimage(540, 200, &character[Active.NowPhoto][0], SRCPAINT);
		
	}

}

void failgame(int fail)
{
	IMAGE imgfail;
     loadimage(&imgfail, "photo/failphoto.jpg", 1200, 640);
	while (fail)
	{
		
		BeginBatchDraw();
		putimage(0, 0, &imgfail);
		FlushBatchDraw();
		system("pause");

		if (GetAsyncKeyState('X'))//x���¿�ʼ
		{
			fail = 0;
			Location.x = 0;
			Location.y = 0;
			mciSendString("close BGM/ʧ��.wav", 0, 0, 0);
		}

		if (GetAsyncKeyState('Z'))//z����������
		{
			cleardevice();
			fail = 0;
			regame = 0;
			overgame = 0;
			mciSendString("close BGM/ʧ��.wav", 0, 0, 0);
			break;
		}
	}
}

void OverGame(int point) {
	IMAGE shenglong[81], imgwin1, imgwin2, imgwin3, imgwin4,imgnewpoint;
	char thepoint[5],name[64];
	int gogame,Gogame;
	int tpoint;
	int i = 0;
	int newmaxfen=0;
	char fpname[64];


	//����ںϳ�̨��Χ����7������Ϳ����ٻ�
    if ((105 - Location.x) > 440 && (105 - Location.x) < 600 && (255 + Location.y) < 270 && (255 + Location.y) > 155 && Number.BeadNumber ==7)
	{
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 3);
		rectangle(656, 240, 763, 290);
		outtextxy(660, 245, "Z�ٻ�");
		//z�ٻ�
		if (GetAsyncKeyState('Z'))
		{
			tpoint = 10000 - 15 * point;//����÷�
			//fscanf(fp, "%s", &maxfen);
			newmaxfen = atoi(maxfen);

			if (tpoint > newmaxfen)//����¼�¼���ļ�
			{
                sprintf_s(fpname, "data/%s", shuru);
				FILE* fp = fopen(fpname, "w+");
				fprintf(fp,"%d",tpoint);
                fclose(fp);
			}
			sprintf_s(thepoint, "%d", tpoint);
			gogame = 1;
			Gogame = 1;
			loadimage(&imgwin1, "photo/win1.jpg", 1200, 640);//Ӯ�Ľ���
			loadimage(&imgwin2, "photo/win2.jpg", 1200, 640);
			loadimage(&imgwin3, "photo/win3.jpg", 780, 480);
			loadimage(&imgwin4, "photo/win4.jpg", 1200, 640);
			loadimage(&imgnewpoint, "photo/newpoint1.jpg", 284, 95);
			while (Gogame) {
				mciSendString("close BGM/bgm2.mp3", 0, 0, 0);

				BeginBatchDraw();
				putimage(0, 0, &imgwin1);
				FlushBatchDraw();
				Sleep(1700);

				mciSendString("open BGM/winbgm.mp3", 0, 0, 0);
				mciSendString("play BGM/winbgm.mp3", 0, 0, 0);

				//�������鶯��
				for (i = 0; i <81; i++)
				{
					 sprintf_s(name, "photo/win/2 (%d).jpg", i + 1);
					loadimage(&shenglong[i], name, 1140, 640);
				}

				for (i = 0; i < 81; i++)//����190s�л�һ��
				{
					BeginBatchDraw();
					putimage(30,0,&shenglong[i]);
					Sleep(190);
					FlushBatchDraw();
				}

				BeginBatchDraw();
				putimage(0, 0, &imgwin4);//Ӯ�Ľ���
				FlushBatchDraw();
				Sleep(2100);
				mciSendString("close BGM/winbgm.mp3", 0, 0, 0);

				BeginBatchDraw();
				putimage(0, 0, &imgwin2);
				mciSendString("open BGM/mingdi.mp3", 0, 0, 0);
				mciSendString("play BGM/mingdi.mp3", 0, 0, 0);
				FlushBatchDraw();
				Sleep(2500);

				while (gogame){//���ص÷�
					BeginBatchDraw();
					putimage(180, 90, &imgwin3);
					outtextxy(480, 283, "�÷֣�");
					outtextxy(575, 282, thepoint);

					if (tpoint > newmaxfen)//�Ƿ��¼�¼
					{
						putimage(430, 335, &imgnewpoint);
					}
					FlushBatchDraw();
					system("pause");
					mciSendString("close BGM/mingdi.mp3", 0, 0, 0);

					if (GetAsyncKeyState('X'))//X���¿�ʼ
					{
						gogame = 0;//���ݳ�ʼ��
						Gogame = 0;
						regame = 0;
						Location.x = 0;
						Location.y = 0;
						lenght = 870;
						mciSendString("open BGM/bgm2.mp3", 0, 0, 0);//����
						mciSendString("play BGM/bgm2.mp3 repeat", 0, 0, 0);
					}

					if (GetAsyncKeyState('Z'))//z������
					{
						cleardevice();//���ݳ�ʼ��
						gogame = 0;
						Gogame = 0;
						regame = 0;
						overgame = 0;
						mciSendString("close BGM/bgm2.mp3", 0, 0, 0);
						break;
						system("pause");
						printf("111111111");
					
					}
				} 
			}

		}
	
	}
}

