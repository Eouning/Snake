//写在前面：
//       本程序所用的音乐仅做学习使用
//       本程序所用图片部分为作者像素画，部分为AI绘成
//       如若造成侵权，立刻删除

#include "Play.h"
#include "framework.h"
#include "大作业.h"

void button(int x, int y, int w, int h, char text[]);
int startUI();
int finishUI(int points);
void BGM1();
void BGM3();
void BGM5();

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    //根据startUI函数返回值判断是否退出游戏
    int exit = 1;
    while (exit == 1) {
        exit = finishUI(startUI());
    }

    return 0;

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//生成按钮。分别输入按钮左上角的坐标，长宽，和储存按钮上文字的字符数组。
void button(int x, int y, int w, int h, char text[]) {
	//生成按钮背景
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	fillroundrect(x, y, x + w, y + h, 10, 10);

	//居中显示按钮文字
	settextstyle(25, 0, "黑体");
	setbkmode(TRANSPARENT);
	double width = textwidth(text) / 2.0;
	double heigh = textheight(text) / 2.0;
	outtextxy(x + 0.5 * w - width, y + 0.5 * h - heigh, text);
}

//开始界面UI。
int startUI() {
	//开始界面背景
	initgraph(650, 400);//背景分辨率
	setbkcolor(WHITE);//背景颜色
	cleardevice();//清空

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "这只是一个普通的窗口名称 O-O");

	IMAGE back;
	loadimage(&back, "20.png", 650, 400);
	drawAlpha(&back, 0, 0);

	BGM1();

	//生成标题
	char title[] = "贪吃蛇~~~";//标题显示的文字
	settextcolor(BLACK);//标题文字的颜色
	settextstyle(50, 0, "黑体");//标题文字的字体
	setbkmode(TRANSPARENT);//让标题字体背景透明
	outtextxy(50, 70, title);

	//生成开始游戏按钮
	char buttonText1[] = "开始游戏";
	button(50, 230, 100, 30, buttonText1);

	//生成退出游戏按钮
	char buttonText2[] = "退出游戏";
	button(450, 230, 100, 30, buttonText2);

	//针对鼠标点击的按键进行相应的事件
	//定义一个鼠标事件的"对象"(便于理解)
	ExMessage msg;
	//不断循环直到鼠标按到按钮
	while (TRUE) {
		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//如果按下了开始游戏按钮
				if (msg.x >= 50 && msg.x <= 150 && msg.y >= 230 && msg.y <= 260) {
					BGM3();
					return Play();//以Play函数的返回值作为startUI函数的返回值，以判定在游戏结束后玩家是否选择回到开始界面
				}
				//如果按下了退出游戏按钮
				else if (msg.x >= 450 && msg.x <= 550 && msg.y >= 230 && msg.y <= 260) {
					BGM3();
					Sleep(1000);
					exit(0);
				}
				break;
			default:
				break;
			}
		}
	}


	closegraph();
}

//结束界面UI
int finishUI(int points) {
	initgraph(650, 400);
	setbkcolor(WHITE);
	cleardevice();

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "猜猜这是不是最后一个普通的窗口名称 ^o^");

	BGM5();

	char title[] = "YOU DIED";
	char words[] = "你的得分是:";

	char score[4];
	score[2] = points % 10 + 48;
	points /= 10;
	score[1] = points % 10 + 48;
	points /= 10;
	score[0] = points % 10 + 48;
	score[3] = '\0';

	settextcolor(RED);
	for (int i = 0; i < 100; i++) {
		cleardevice();
		settextstyle(50 + i, 0, "楷体");
		setbkmode(TRANSPARENT);
		int width = textwidth(title) / 2;
		outtextxy(325 - width, 70, title);
	}

	IMAGE back;
	loadimage(&back, "21.png", 650, 400);
	drawAlpha(&back, 0, 200);

	int width = textwidth(words) / 2;
	settextcolor(BLACK);
	settextstyle(25, 0, "黑体");
	setbkmode(TRANSPARENT);
	width = textwidth(words) / 2;
	outtextxy(100 - width, 30, words);
	outtextxy(100 + width, 30, score);

	char buttonText2[] = "退出游戏";
	button(400, 230, 100, 30, buttonText2);

	char buttonText1[] = "回到主页";
	button(100, 230, 100, 30, buttonText1);

	ExMessage msg;

	while (1) {
		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//如果按下了开始游戏按钮
				if (msg.x >= 100 && msg.x <= 200 && msg.y >= 230 && msg.y <= 260) {
					BGM3();
					return 1;//以Play函数的返回值作为startUI函数的返回值，以判定在游戏结束后玩家是否选择回到开始界面
				}
				//如果按下了退出游戏按钮
				else if (msg.x >= 400 && msg.x <= 500 && msg.y >= 230 && msg.y <= 260) {
					BGM3();
					Sleep(1000);
					exit(0);
				}
				break;
			default:
				break;
			}
		}
	}
}

//BGM
//开始界面背景音乐
void BGM1() {
	//在开始时关闭本音乐，防止无法二次播放
	mciSendString("close 01", NULL, 0, NULL);
	//打开音乐，播放音乐
	mciSendString("open ./01startUI.wav alias 01", 0, 0, 0);
	mciSendString("play 01", 0, 0, 0);
}

//按钮按下音效
void BGM3() {
	mciSendString("close 01", NULL, 0, NULL);
	mciSendString("close 05", NULL, 0, NULL);
	mciSendString("close 03", NULL, 0, NULL);
	//打开音乐，播放音乐
	mciSendString("open ./03button.wav alias 03", 0, 0, 0);
	mciSendString("play 03", 0, 0, 0);
}

//死亡音效
void BGM5() {
	mciSendString("close 02", NULL, 0, NULL);
	mciSendString("close 05", NULL, 0, NULL);
	//打开音乐，播放音乐
	mciSendString("open ./05death.wav alias 05", 0, 0, 0);
	mciSendString("play 05", 0, 0, 0);
}
