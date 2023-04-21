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
//                          Amen··· 

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



typedef struct prop {  //用结构体存储龙珠和道具，其中1-7为龙珠1234567
	int x;              //x为龙珠和道具的横坐标，y为纵坐标    
	int y;
	int have=0;  //是否拾取0代表未拾取，，，，1代表拾取
	int food=0;//食物数量
	int medicine=0;//药水数量
	struct prop* next;
}PROP;

typedef struct nouss {  //链表2用于控制道具拾取后的插入删除
	int x=0;             
	int idnowHave = 0; 
	char name[10] = "0";
	int theFoodHave = 0;
	struct nouss* next;
}NO;

typedef struct number{
	int chNumber;//人物选择第几个
	int BeadNumber;//龙珠数量
	int MedNum;//药数量
	int FoodNum;//食物数量
}NUM;

typedef struct location{//地图位置xy
	int x = 0;
	int	y = 0;//
	int BackageX = 0;
	int BackageY = 0;
}LOC;

typedef struct active{
	int Music2;//游戏音乐是否打开
	int PhotoWalk;//人物行走的图片
	int NowPhoto;//当前朝向位置图片
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
PROP* create();//创建链表
void buylh();//购买凌华界面
void jiazaibg();//加载初始背景动画
void bgm();//页面bgm播放
void bgms();//游戏bgm播放
void newData();
void closebgm();//关闭bgm
void choicech();//选择人物
void qiephoto();//切换页面
void xychange();//xy坐标改变
void jingdutiao(int chang);//进度条
int gametime(time_t t1);//时间
void chushi();//初始界面
void thetime(int putgametime);//游戏时间显示
int shezhi();//设置界面
void PutProp(PROP* h);//道具背包加载
void pack(PROP* h);//背包
void stoneDown(int Time);
void putcharacter();//人物行动
void failgame(int fail);//失败界面
void OverGame(int point);//游戏胜利
PROP* putimage(PROP* h);//在地图加载道具
PROP* TakeProp(PROP* h);//拾取道具
PROP* UseMFProp(PROP* h,int time);//使用medicine和food
int UseProp(PROP* h,int Pnumber);//使用道具
void propPhoto();//打开背包界面的选择框和道具介绍
void FindProp(PROP* h);//寻找道具
void kbfree();//释放键盘输入
NO* nouse(NO*h);

NUM Number;
LOC Location;
ACT Active;
STONE Stone;
int speed,ifspeed;//速度和使用道具后速度
char shuru[10];//uid
char maxfen[5] = "0000";//最高分
int lenght = 870;//进度条的长度
int medthetime = 0,TIMEi=1;//时间控制
int IfUseProp,ifjump;//是否使用道具，跳
int regame = 1,overgame = 1;//继续游戏控制//重新开始游戏控制
int PackPropXY[12][2] = { {160,63},{320,65},{460,63},{160,210},{310,207},{470,210},{160,350},{315,350},{470,355},{160,490},{310,490} };//背包格子的坐标
int PackPropNumber = 0;//拾取道具的数量
time_t t1;//开始游戏的time
IMAGE propphoto[11],propphotobk[11];
IMAGE useprop[11];


int main()
{
	IMAGE imgnewbk, img1, img2, imgdi,imgsmalldi, imgfail, imgpack[3];
	IMAGE img111, img222, imgmedicine[3],imgfood[3];
	IMAGE imgshezhi[3], imgyinyue[3],imgfind[3], imgshezhiphoto, imghct1, imghct2;
	char fpname[64];
	
	int lenghttime = 0, timechange = 1,TheSetTime,Settime;
	int sy = 1,newbgm=0;//bgm开关判断
	int qie = 1;//如果切换页面就关闭bgm1
	int fail = 0;//失败控制
	int gogame = 1;//游戏循环控制
	int gamethetime;//游戏时间
	PROP* head;
	PROP* prophead;
	NO* nouses;

	initgraph(1200, 640, SHOWCONSOLE);
    chushi();
	loadimage(&imgdi, "photo/photo4.jpg", HEIGHT, WIDTH);
	loadimage(&imgsmalldi, "photo/smalldi.jpg", 150, 150);
	loadimage(&imgshezhi[0], "photo/shezhi.jpg", 35, 35);//设置
	loadimage(&imgshezhi[1], "photo/shezhi-.jpg", 35, 35);
	loadimage(&imgshezhi[2], "photo/R.jpg", 18, 18);
	loadimage(&imgyinyue[0], "photo/shenyin.jpg", 35, 35);//音乐
	loadimage(&imgyinyue[1], "photo/shenyin-.jpg", 35, 35);
	loadimage(&imgyinyue[2], "photo/T.jpg", 18, 18);
	loadimage(&imgfind[0], "photo/find.jpg", 35, 35);
	loadimage(&imgfind[1], "photo/find-.jpg", 35, 35);
	loadimage(&imgfind[2], "photo/Q.jpg", 18, 18);
	loadimage(&img1, "photo/图1.jpg", 135, 320);//人物
	loadimage(&img2, "photo/1.jpg", 135, 320);
	loadimage(&imgpack[0], "photo/背包1.jpg", 60, 60);//背包
	loadimage(&imgpack[1], "photo/背包2.jpg", 60, 60);
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
    InputBox(shuru, 100, "请输入UID：（1-8位数字,字母或汉字）");
	while(1)
	{
		if ( strlen(shuru)==0 || shuru[0] == ' '|| shuru[0] == '.'||shuru[0] == ','||shuru[0] == '/') {
			InputBox(shuru, 100, "无效输入！请重新输入UID：（1-8位数字,字母或汉字）");
		}
		else{
			break;
		}
	}

		buylh();

		srand((unsigned)time(NULL));
	//加载页面
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
	
         //判断切换页面和bgm开关
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

				 //绘制游戏界面
				 Location.BackageX = -HEIGHT/2 - Location.x+600;
				 Location.BackageY = -WIDTH/2 + Location.y+540;
				 putimage(Location.BackageX,Location.BackageY, &imgdi);
				 //绘制合成台
				 putimage(105 - Location.x, 255 + Location.y, &imghct2, SRCAND);
				 putimage(105 - Location.x, 255 + Location.y, &imghct1, SRCPAINT);
				 
				 gamethetime = gametime(t1);
				 lenghttime = gamethetime;
				 if(timechange==0){nouses=nouse(nouses);}
				 stoneDown(gamethetime);
				 //绘制道具
				  prophead = putimage(head);
				 prophead = TakeProp(prophead);
				 prophead = UseMFProp(prophead,gamethetime);
				 //寻找图标
				 putimage(1050, 15, &imgfind[0], SRCAND);
				 putimage(1050, 15, &imgfind[1], SRCPAINT);
				 putimage(1060, 55, &imgfind[2]);
				 //设置图标
				 putimage(1100, 15, &imgshezhi[0], SRCAND);
				 putimage(1100, 15, &imgshezhi[1], SRCPAINT);
				 putimage(1110, 55, &imgshezhi[2]);
				 //音乐图标
				 putimage(1150, 15, &imgyinyue[0], SRCAND);
				 putimage(1150, 15, &imgyinyue[1], SRCPAINT);
				 putimage(1160, 55, &imgyinyue[2]);


				 //绘制背包
				 putimage(15, 550, &imgpack[1], SRCAND);
				 putimage(15, 550, &imgpack[0], SRCPAINT);
				 putimage(73, 605, &imgpack[2]);
				 //药水图标
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
				 //食物图标
				 if (Number.FoodNum == 0) {
					 putimage(1120, 169, &imgfood[1], SRCAND);
					 putimage(1120, 169, &imgfood[2], SRCPAINT);
				 }
				 else
				 {
					 putimage(1120, 169, &imgfood[1], SRCAND);
					 putimage(1120, 169, &imgfood[0], SRCPAINT);
				 }
				 //药水和食物的1，2提示
				 putimage(1169, 144, &img111);
				 putimage(1169, 205, &img222);

				 //输入uid
				 outtextxy(965, 555, "UID:");
				 outtextxy(1044, 555, shuru);
				 //绘制小地图
				 setlinecolor(WHITE); //设置框颜色
				 setlinestyle(PS_SOLID, 2);
				 rectangle(5, 5, 159, 159);
				 putimage(7, 7, &imgsmalldi);//小地图图片
				 setfillcolor(RGB(115,253,255));
				 if(77+Location.x / 39>=7&& 81 - Location.y / 28>=7&&77+Location.x / 39<=157&& 81 - Location.y / 28<=157){//在小地图范围内加载人物位置
				     solidcircle(77 + Location.x/39, 81 - Location.y/28, 3);//人物位置
				 }
				 //进度条随时间减少
				 if (lenghttime- Settime >= DELINRTIME*timechange)
				 {
					 lenght = lenght -DELINEBOOD;
					 lenghttime = 0;
					 timechange++;
				 }
			 //游戏时间
				 
				 Settime += TheSetTime;
				 thetime(gamethetime- Settime);
				 //进度条
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
			 //游戏结束判断
			 if (lenght <= 325)
			 {
				 regame = 0;
				 fail = 1;
				 mciSendString("open BGM/失败.wav", 0, 0, 0);
				 mciSendString("play BGM/失败.wav", 0, 0, 0);
			 }

			 FlushBatchDraw();
			//失败界面
			 failgame(fail);
			 //按q寻找
			 if (GetAsyncKeyState('Q'))
			 {
				 FindProp(prophead);
			 }
			 TheSetTime = shezhi();//设置
			 pack(prophead);
			 kbfree();//释放按键
			}	
	      }

	}


	//getchar();
	closegraph();
	return 0;
}


//自定义函数部分
int ifMouseHit(int qie) {
	if (MouseHit())
	{

		MOUSEMSG msg = GetMouseMsg();

		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (msg.x > 500 && msg.x < 680 && msg.y>540 && msg.y < 590)
			{
				qiephoto();//切换页面
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
			
			//bgm开关
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

	//加载最高分
	settextcolor(RED);
	settextstyle(45, 0, 0);
	setbkmode(TRANSPARENT);
	outtextxy(150, 50, "最高分：");
	outtextxy(285, 50, maxfen);

	settextcolor(WHITE);
	outtextxy(1044, 555, shuru);
	FlushBatchDraw();
}



void chushi()//加载初始界面
{
	IMAGE chushi[9],imgchushi;
	IMAGE jiazai[8],imgjiazai;
	char arry[64];
	char name[64];
    printf("1111");
	mciSendString("open BGM/hailang.mp3", 0, 0, 0);//播放音乐
	
	int i = 0;
	
	loadimage(&imgjiazai, "photo/jiazai/9.jpg", 1200, 640);

    mciSendString("play BGM/hailang.mp3 repeat", 0, 0, 0);
	for ( i = 0; i < 9;i++)//加载图片
	{	
		sprintf_s(arry,"photo/chushi%d.jpg",i+1);
		loadimage(&chushi[i],arry,1200,640);
		
	}
	for (i = 0; i < 7; i++)//没个1900s切换1个图片
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

void bgm()//控制音乐开关
{
	mciSendString("open BGM/岛屿bgm.mp3", 0, 0, 0);
	mciSendString("play BGM/岛屿bgm.mp3 repeat", 0, 0, 0);
}



void closebgm() {//控制音乐开关
	int sy = 1;
	if (sy == 1) {
		mciSendString("close BGM/岛屿bgm.mp3", 0, 0, 0);
		sy = 0;
	}
	else {
		mciSendString("play BGM/岛屿bgm.mp3", 0, 0, 0);
		sy = 1;
	}
}




void bgms()
{
	mciSendString("open BGM/bgm2.mp3", 0, 0, 0);
	mciSendString("play BGM/bgm2.mp3 repeat", 0, 0, 0);
}

void newData() {//初始化数据
	
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

//切换页面
void qiephoto() {
	IMAGE img,src,img1,img2,imgchinteroduce,imgpack1,imgpack2,imglh1,imglh2;
	int chinteroduce;
	chinteroduce = 1;
	mciSendString("close BGM/amsg.mp3", 0, 0, 0);
    loadimage(&img, "photo/photo4.jpg", HEIGHT, WIDTH);
	loadimage(&img1, "photo/图1.jpg", 143, 320);
	loadimage(&img2, "photo/1.jpg", 143, 320);
    loadimage(&imglh1, "photo/lh1.jpg", 150, 320);
	loadimage(&imglh2, "photo/lh2.jpg", 150, 320);
	loadimage(&imgpack1, "photo/背包1.jpg", 60, 60);
	loadimage(&imgpack2, "photo/背包2.jpg", 60, 60);

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
	outtextxy(480,300,"请准备开始游戏");

	
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


//选择人物
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
		
		
		if (GetAsyncKeyState('A'))//a向左
		{
			j--;
		}

		if (GetAsyncKeyState('D'))//d向右
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


//xy地图位置改变
void xychange() {

	if ((Location.BackageX-speed) > -HEIGHT +1300 && (Location.BackageX +speed)<-500 && (Location.BackageY-speed) > -WIDTH + 650 &&(Location.BackageY +speed)< -200)
	{
	     if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	     {
			 Location.y = Location.y + speed;//上
			 ifspeed = 0;
	      }
	     if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	      {
			 Location.y = Location.y - speed;//下
			  ifspeed = 0;
	        }
	     if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	     {
			 Location.x = Location.x - speed;//左
				ifspeed = 0;
	      }
	     if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	     {
			 Location.x = Location.x + speed;//右
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

//游戏时间计算
int gametime(time_t t1)
{
	time_t t2;
	int interval;
	t2 = time(NULL);
	interval = t2 - t1;

	return interval;

}


//游戏时间显示
void thetime(int putgametime) {
	char fen[20] = "0";
	char miao[20]="0";
	int thefen=0;
	int themiao=0;
	
	themiao = putgametime;
	if (themiao >= 60*TIMEi)//秒大于60就=0，分++
	{

		thefen=thefen+1;
		//
		TIMEi++;
	}
    //时间计算与打印
	sprintf_s(fen, "%2d",TIMEi-1 );//int转char
	sprintf_s(miao, "%2d", themiao-60*(TIMEi - 1));
	outtextxy(547, 20, "0");
	outtextxy(557,20,fen);//分
	outtextxy(585, 17, ":");
	outtextxy(594, 20, miao);//秒
}




//进度条
void jingdutiao(int chang)
{

	setfillcolor(GREEN);  //设置进度条填充颜色
	setlinecolor(WHITE); //设置进度条框颜色
	setlinestyle(PS_SOLID, 1);//进度条框
	rectangle(324,569,871,586);//进度条框位置
	if(lenght>325)
	   bar(325,570,lenght,585);//填充进度条
}



void stoneDown(int Time) {
	int i;
	if (Time - Stone.StoneTime <10) {//每10s一个循环
	  
	    if(Stone.StoneNum==0)
	    { 
			i= rand() % 520;
            Stone.newy = rand() % 520;//随机生产石头xy坐标
			Stone.newx = rand() % 1000;		
			Stone.StoneNum++;//只进行一次
		}
		Stone.x = 50+Stone.newx- Location.x+Stone.newposx;//石头随屏幕运动
		Stone.y = 50 +Stone.newy + Location.y-Stone.newposy;
		if (Time >= Stone.StoneTime && Time < Stone.StoneTime + 3)//0-3s红色提示圈
		{
			setfillcolor(RED);//红色
			setlinecolor(RED); //设置框颜色
			setlinestyle(PS_SOLID, 12);
			circle(Stone.x, Stone.y, 70);//圆环
			fillcircle(Stone.x, Stone.y, 20);//中心圆
			Stone.stoney = -250;//最开始陨石在屏幕外
			mciSendString("close BGM/boinbgm.mp3", 0, 0, 0);
			Stone.stonetime = 0;//记录扣血次数每循环一次就归零，只有=0时扣血，之后就加1
		}
		else if (Time >= Stone.StoneTime + 3 && Stone.stoney + 220 < Stone.y && Stone.stonetime == 0)
		{
			putimage(Stone.x - 60, Stone.stoney, &Stone.imgstone[1], SRCAND);//绘制陨石
			putimage(Stone.x - 60, Stone.stoney, &Stone.imgstone[0], SRCPAINT);
			if (GetAsyncKeyState('A') || GetAsyncKeyState('D') || GetAsyncKeyState('S'))//陨石下降速度
			{
				Stone.stoney += 89;
			}
			else if (GetAsyncKeyState('W')) {//速度
				Stone.stoney += 120;
			}
			else {//速度
				Stone.stoney += 39;
			}


		}
		else if (Time <= Stone.StoneTime + 5)//陨石落下到5s加载爆炸背景和声音
		{
			if (Stone.stonetime == 1 && Stone.x - 70 > 480 && Stone.x - 70 < 620 && Stone.y - 70 > 340 && Stone.y - 70 < 470) {//判别是否扣血
				lenght = lenght - 45;//血条减少
			}
			//printf("          %d    \n", Time - Stone.StoneTime);
			mciSendString("open BGM/boinbgm.mp3", 0, 0, 0);//声音
			mciSendString("play BGM/boinbgm.mp3", 0, 0, 0);
			Stone.stonetime++;//只扣一次血
			putimage(Stone.x - 80, Stone.y - 80, &Stone.imgbobm[1], SRCAND);//爆炸图片
			putimage(Stone.x - 80, Stone.y - 80, &Stone.imgbobm[0], SRCPAINT);

		}
		else
			printf("1");
    }
	else
	{
		Stone.StoneTime = Time;//10s外后重置参数
		Stone.StoneNum = 0;
		Stone.newposx = Location.x;
		Stone.newposy = Location.y;
	}

}


//设置
int shezhi() {
	time_t settime = time(NULL);
	IMAGE imgshezhiphoto;
	int gogame=1;
	if (GetAsyncKeyState('R'))//r设置
	{
		gogame = 1;
		loadimage(&imgshezhiphoto, "photo/shezhiphoto.jpg", 800, 500);
        mciSendString("open BGM/shezhibgm.wav", 0, 0, 0);
		mciSendString("play BGM/shezhibgm.wav", 0, 0, 0);
		while (gogame) {
			// printf("坐标位置%d   %d\n ", msg1.x, msg1.y);
			
			BeginBatchDraw();
			putimage(200, 80, &imgshezhiphoto);
			FlushBatchDraw();
            system("pause");
			//c继续
			if (GetAsyncKeyState('C'))//c继续游戏
			{
				gogame = 0;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
				break;
			}
			//x重新开始
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

			if (GetAsyncKeyState('Z'))//z主界面
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



	if (GetAsyncKeyState('T'))//t音乐
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

void pack(PROP* h)//背包
{
	IMAGE imgpackbg;
	int gogame = 1;
	int Pnumber;
	Pnumber = 0;
	if (GetAsyncKeyState('G'))//G打开背包
	{
		Sleep(200);
		gogame = 1;
		loadimage(&imgpackbg, "photo/packbg.jpg", 1000, 600);
		mciSendString("open BGM/shezhibgm.wav", 0, 0, 0);
		mciSendString("play BGM/shezhibgm.wav", 0, 0, 0);
		IfUseProp = 0;
		while (gogame) {//循环加载界面
			BeginBatchDraw();
			putimage(100, 20, &imgpackbg);
			PutProp(h);
			Pnumber=UseProp(h,Pnumber);
			FlushBatchDraw();
			Sleep(300);
			//c继续
			if (GetAsyncKeyState('X'))
			{
				gogame = 0;
				mciSendString("close BGM/shezhibgm.wav", 0, 0, 0);
			}
		}

	}
}


PROP* UseMFProp(PROP* h,int time) {//使用道具
	PROP* r, * p;
	p = h;
	int i = 0;

	if (time - medthetime > 20)
	{
		speed = 35;
	}
	if (GetAsyncKeyState('1')&&Number.MedNum!=0)//按1 是使用药水  且物品数量不为0
	{
		Sleep(100);
		for (i = 0; i < 11; i++)//遍历链表寻找道具并将道具标记为已使用
		{
			if (p->medicine == 1)//游戏速度增加
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
	
	if (GetAsyncKeyState('2') && Number.FoodNum != 0)//按2 使用食物
	{
		Sleep(100);
		for (i = 0; i < 11; i++)//同上
		{
			if (p->food == 1)
			{
				p->have = 2;
				p->food = 2;
				Number.FoodNum--;
				lenght = lenght + 100;
				if (lenght > 870)//进度条的增加
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



int UseProp(PROP* h,int Pnumber) {//打开背包界面的选择框和道具介绍

	PROP * p;
	p = h;
	int i = 0;
	char name[64];
	IfUseProp = 0;
	mciSendString("close BGM/chakprop.mp3", 0, 0, 0);
	mciSendString("open BGM/chakprop.mp3", 0, 0, 0);
	
	for (i = 0; i < 11; i++)
	{

		if (p->have == 1)//加载道具介绍图片
		{
			sprintf_s(name, "photo/propuse/%d.jpg", i + 1);
			loadimage(&useprop[IfUseProp], name, 475, 455);
			IfUseProp++;
		}

		p = p->next;
	}
	
	for (i = IfUseProp; i < 11; i++)//加载空白介绍bk
	{
		loadimage(&useprop[i], "photo/propuse/12.jpg", 475, 455);
	}
	//选择框
	putimage(590,127, &useprop[Pnumber]);
	setlinecolor(RED); //设置进度条框颜色
	setlinestyle(PS_SOLID, 5);
	rectangle(PackPropXY[Pnumber][0]-15, PackPropXY[Pnumber][1]-15, PackPropXY[Pnumber][0]+93, PackPropXY[Pnumber][1]+93);
	//选择道具移动
	if (GetAsyncKeyState('W'))//w向上
	{
		if (Pnumber > 2&& Pnumber<11) {
			Pnumber = Pnumber - 3;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);

		}
	}
	if (GetAsyncKeyState('S'))//s向下
	{
		if (Pnumber <8 ) {
			Pnumber = Pnumber + 3;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);

		}
	}
	if (GetAsyncKeyState('A'))//a向左
	{
		if(Pnumber >0 && Pnumber <11){
			Pnumber--;
			mciSendString("play BGM/chakprop.mp3", 0, 0, 0);
         }
	}
	if (GetAsyncKeyState('D'))//的向右
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



//链表建立
PROP* create()
{
	PROP* p, * check = NULL, *r = NULL, * head = NULL;
	int i,j=0,n=1;
	int xx = 0;
	int yy = 0;
	int ifmax;//判断坐/标差距平方是否大于1000000
	p = head;
    srand((unsigned)time(NULL));
	for (i = 0; i < 11; i++)
	{
		while(1){
		     p = (PROP*)malloc(sizeof(PROP));//动态创建链表
			if (p != NULL)
			{
				break;
			}
		}
		while(1)
		{
			ifmax = 0;
			check = head;
			p->x = rand() % (HEIGHT - 3000) + 1400;//随机产生坐标
			p->y = rand() % (WIDTH - 2200) + 1100;//y的坐标
			for (j = 0; j < i; j++)
			{
				//判断距离大小
				if ((p->x - check->x) * (p->x - check->x) + (p->y - check->y) * (p->y - check->y) > 360000)
				{
					ifmax++;
				}
				check = check->next;

			}
			if (ifmax == j)//判断是否都符合条件
			{
				break;
			}
			
		}

			p->have = 0;//have控制拾取  初始为0表示全部未拾取
			p->medicine = 0;//药品数量记录
			p->food = 0;//食物数量记录

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


//导入道具图片
void propPhoto()
{
	char Pname[64];
	char Parry[64];
	int i;
	//加载道具图片
	for(i=0;i<11;i++){
	sprintf_s(Pname, "photo/prop/%d.jpg", i+1);
	sprintf_s(Parry, "photo/prop/-%d.jpg", i+1);
	loadimage(&propphoto[i], Pname, 80, 80);
	loadimage(&propphotobk[i], Parry, 80, 80);
	}
}

NO* nouse(NO*h) {//道具链表的删除与插入
	NO* p, * r;
	h->x = 0;
	while (h != NULL)
	{
		h->idnowHave = 0;
		h->theFoodHave = 0;
		p = h;
		r = p->next;
		while (r != NULL) {
			if (r->x != h->x)//如果俩个道具的下坐标不相同则插入一个道具链表
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
			else//否则就删除其中一个并提示
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



//如道具未拾取就在地图上加载道具图片
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


//拾取道具
PROP* TakeProp(PROP* h) {

	PROP* r, * p;
	p = h;
	int i = 0;
	for (i = 0; i < 11; i++)
	{
       //判断是否在可拾取的范围内
		if (p->have ==0&& p->x + Location.BackageX<=630 && p->x + Location.BackageX >= 530 && p->y + Location.BackageY<= 450 && p->y + Location.BackageY >= 250)
		{
		//	printf("位于坐标内\n");
			setlinecolor(WHITE);
			setlinestyle(PS_SOLID, 3);
			rectangle(656,240,763,290); 
			outtextxy(660,245,"F拾取");
			//如果按f就拾取
			if (GetAsyncKeyState('F'))
			{
				p->have = 1;//拾取就让have=1，就不在地图上加载了

				if (i == 7 || i ==8)
				{
					p->medicine = 1;//如果是药就标记一下   food同理
					Number.MedNum++;
				}

				if (i == 9|| i == 10)
				{
					p->food = 1;
					Number.FoodNum++;//食物量加一
				}

				mciSendString("close BGM/takeprop.mp3", 0, 0, 0);
				mciSendString("open BGM/takeprop.mp3", 0, 0, 0);
				mciSendString("play BGM/takeprop.mp3", 0, 0, 0);
				if (i<7)//龙珠的数量+1
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



//背包加载道具
void PutProp(PROP* h) {

	PROP* r, * p;
	p = h;
	r = h;
	int i = 0;
	PackPropNumber = 0;
	for (i = 0; i < 11; i++)
	{
		
		if (p->have == 1)//如果have是1就加载道具
		{
			printf("\n%d          %d\n",i,p->have );//加载图片
			putimage(PackPropXY[PackPropNumber][0], PackPropXY[PackPropNumber][1], &propphotobk[i], SRCAND);
			putimage(PackPropXY[PackPropNumber][0], PackPropXY[PackPropNumber][1], &propphoto[i], SRCPAINT);
			PackPropNumber++;
		}

		p = p->next;
	}

}



//寻找道具
void FindProp(PROP* h) {

	PROP * p;
	p = h;
	int i = 0;
	int theX=0, theY=0;
	setlinecolor(WHITE);//设置直线格式
	setlinestyle(PS_DASH,8);

	for (i = 0; i < 11; i++)
	{
		
		if (p->have == 0)
		{
			//按排最前面的寻找
			BeginBatchDraw();
			theX = (p->x + Location.BackageX - 605) / 20;//坐标只差除以20；
			theY= (p->y + Location.BackageY - 505) / 20;
			line(605,505,theX+605,theY+505);
			FlushBatchDraw();
			Sleep(500);//延迟500s
			break;
		}

		p = p->next;
	}

}


//释放未点击的键位
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




//人物行动
void putcharacter() {

	IMAGE character[4][5];
	IMAGE characterbk[4][5];
	char name[64];
	char namebk[64];
	int i, j;
	if (Active.PhotoWalk >= 4)
	{
		Active.PhotoWalk = Active.PhotoWalk - 4;//一直在1-4循环
	}
	
	//加载图片
	
	for (i = 0; i < 4; i++)//加载背景图
	{
		for(j=0;j<5;j++)
		{
			sprintf_s(name, "character/%d/%d/%d.jpg", Number.chNumber,i + 1,j+1);
			loadimage(&character[i][j], name, 143, 320);
		}
	}

	for (i = 0; i < 4; i++)//加载掩码图
	{
		for (j = 0; j < 5; j++)
		{
			sprintf_s(namebk, "character/%d/%d/-%d.jpg", Number.chNumber,i + 1,j+1);
			loadimage(&characterbk[i][j], namebk, 143,320);
		}
	}

	
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//wsad上下左右
	{
		putimage(540, 200, &characterbk[1][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[1][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))//wsad上下左右
	{
		putimage(540, 200, &characterbk[0][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[0][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))//wsad上下左右
	{
		putimage(540, 200, &characterbk[2][Active.PhotoWalk], SRCAND);
		putimage(540, 200, &character[2][Active.PhotoWalk], SRCPAINT);
		Sleep(200);
		Active.PhotoWalk++;
		Active.NowPhoto = 2;
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))//wsad上下左右
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

	else {//未移动时的界面
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

		if (GetAsyncKeyState('X'))//x重新开始
		{
			fail = 0;
			Location.x = 0;
			Location.y = 0;
			mciSendString("close BGM/失败.wav", 0, 0, 0);
		}

		if (GetAsyncKeyState('Z'))//z返回主界面
		{
			cleardevice();
			fail = 0;
			regame = 0;
			overgame = 0;
			mciSendString("close BGM/失败.wav", 0, 0, 0);
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


	//如果在合成台范围内且7个龙珠就可以召唤
    if ((105 - Location.x) > 440 && (105 - Location.x) < 600 && (255 + Location.y) < 270 && (255 + Location.y) > 155 && Number.BeadNumber ==7)
	{
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 3);
		rectangle(656, 240, 763, 290);
		outtextxy(660, 245, "Z召唤");
		//z召唤
		if (GetAsyncKeyState('Z'))
		{
			tpoint = 10000 - 15 * point;//计算得分
			//fscanf(fp, "%s", &maxfen);
			newmaxfen = atoi(maxfen);

			if (tpoint > newmaxfen)//如果新纪录输文件
			{
                sprintf_s(fpname, "data/%s", shuru);
				FILE* fp = fopen(fpname, "w+");
				fprintf(fp,"%d",tpoint);
                fclose(fp);
			}
			sprintf_s(thepoint, "%d", tpoint);
			gogame = 1;
			Gogame = 1;
			loadimage(&imgwin1, "photo/win1.jpg", 1200, 640);//赢的界面
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

				//加载龙珠动画
				for (i = 0; i <81; i++)
				{
					 sprintf_s(name, "photo/win/2 (%d).jpg", i + 1);
					loadimage(&shenglong[i], name, 1140, 640);
				}

				for (i = 0; i < 81; i++)//动画190s切换一张
				{
					BeginBatchDraw();
					putimage(30,0,&shenglong[i]);
					Sleep(190);
					FlushBatchDraw();
				}

				BeginBatchDraw();
				putimage(0, 0, &imgwin4);//赢的界面
				FlushBatchDraw();
				Sleep(2100);
				mciSendString("close BGM/winbgm.mp3", 0, 0, 0);

				BeginBatchDraw();
				putimage(0, 0, &imgwin2);
				mciSendString("open BGM/mingdi.mp3", 0, 0, 0);
				mciSendString("play BGM/mingdi.mp3", 0, 0, 0);
				FlushBatchDraw();
				Sleep(2500);

				while (gogame){//加载得分
					BeginBatchDraw();
					putimage(180, 90, &imgwin3);
					outtextxy(480, 283, "得分：");
					outtextxy(575, 282, thepoint);

					if (tpoint > newmaxfen)//是否新纪录
					{
						putimage(430, 335, &imgnewpoint);
					}
					FlushBatchDraw();
					system("pause");
					mciSendString("close BGM/mingdi.mp3", 0, 0, 0);

					if (GetAsyncKeyState('X'))//X重新开始
					{
						gogame = 0;//数据初始化
						Gogame = 0;
						regame = 0;
						Location.x = 0;
						Location.y = 0;
						lenght = 870;
						mciSendString("open BGM/bgm2.mp3", 0, 0, 0);//音乐
						mciSendString("play BGM/bgm2.mp3 repeat", 0, 0, 0);
					}

					if (GetAsyncKeyState('Z'))//z主界面
					{
						cleardevice();//数据初始化
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

