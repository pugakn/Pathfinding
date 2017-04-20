// pathfinding.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "pathfinding.h"
#include "DFSWalker.h"
#include "BFSWalker.h"
#include "BestFSWalker.h"
#include "DijikstraWalker.h"
#include "AstarWalker.h"
#include <vector>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // Instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
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

    // TODO: colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PATHFINDING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PATHFINDING));

    MSG msg;

    // Bucle principal de mensajes:
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
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: registrar la clase de ventana.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PATHFINDING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PATHFINDING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

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
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  procesar mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
#include <vector>
#define DEFAULT_WEIGHT 1
#define MEDIUM_WEIGHT 10
#define HIGH_WEIGHT 20

#define BUTTON_START      1001
#define BUTTON_BLOCK      1002
#define BUTTON_SEARCH     1003
#define BUTTON_RESET      1004
#define BUTTON_M05		  1005
#define BUTTON_M1		  1006

namespace SelectedTool
{
	enum E
	{
		START,
		BLOCK,
		MWEIGHT,
		HWEIGHT
	};
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int iAncho, iAlto, iDivX, iDivY;
	static int graphWidth = 50;
	int iCordx, iCordy;
	static HBRUSH hColor;
	static HBRUSH hColorRed;
	static HBRUSH hColorBlue, hColorMW, hColorHW, hColorClosed;

	static std::vector<GraphNode> nodes;
	nodes.resize(graphWidth*graphWidth);

	static CWalkerBase* walker;
	static CWalkerBase* dfs;
	static CWalkerBase* bfs;
	static CWalkerBase* bestfs;
	static CWalkerBase* djikstra;
	static CWalkerBase* astar;
	static Heuristic::E actualEuristic;
	static std::vector<GraphNode*> path;
	static std::list<GraphNode*> closedList;
	static SelectedTool::E tool;
	static GraphNode* graphInicio;
	static GraphNode* graphFinal;
	static bool bSearched = false;
	//static HWND hButton;

    switch (message)
    {
	case WM_CREATE:
	{
		graphInicio = &nodes[0];
		graphFinal = &nodes[0];
		int id = 0;
		for (int i = 0; i < graphWidth; i++)//filas
			for (int j = 0; j < graphWidth; j++)//columnas
			{
				nodes[i + j * graphWidth].id = id++;
				nodes[i + j * graphWidth].worldPosition = Vector3D(i,j,1);
				nodes[i + j * graphWidth].weight = DEFAULT_WEIGHT;

				if (j + 1 < graphWidth)
				{
					nodes[i + j *graphWidth].children.push_back(&nodes[i + (j + 1) * graphWidth]);
					if (i + 1 < graphWidth)
						nodes[i + j * graphWidth].children.push_back(&nodes[i+1 + (j + 1) * graphWidth]);
					if (i - 1 >= 0)
						nodes[i + j * graphWidth].children.push_back(&nodes[i - 1 + (j + 1) * graphWidth]);
				}
				if (j - 1 >= 0)
				{
					nodes[i + j * graphWidth].children.push_back(&nodes[i + (j - 1) * graphWidth]);
					if (i + 1 < graphWidth)
						nodes[i + j * graphWidth].children.push_back(&nodes[i + 1 + (j - 1) * graphWidth]);
					if (i - 1 >= 0)
						nodes[i + j * graphWidth].children.push_back(&nodes[i - 1 + (j - 1) * graphWidth]);
				}
				if (i + 1 < graphWidth)
				{
					nodes[i + j *graphWidth].children.push_back(&nodes[i + 1 + j * graphWidth]);
				}
				if (i - 1 >= 0)
				{
					nodes[i + j * graphWidth].children.push_back(&nodes[i - 1 + j * graphWidth]);
				}


			}
		dfs = new CDFSWalker();
		bfs = new CBFSWalker();
		bestfs = new CBestFSWalker();
		djikstra = new CDijikstraWalker();
		astar = new CAstarWalker();

		walker = astar;
		actualEuristic = Heuristic::E::kEuclidean;
		walker->SetHeuristic(actualEuristic);
		//Inicializar Brochas
		hColor = CreateSolidBrush(RGB(150, 150, 65));
		hColorRed = CreateSolidBrush(RGB(150, 0, 0));
		hColorBlue = CreateSolidBrush(RGB(0, 0, 150));
		hColorClosed = CreateSolidBrush(RGB(50, 50, 50));
		hColorMW = CreateSolidBrush(RGB(0, 255, 0));
		hColorHW = CreateSolidBrush(RGB(0, 200, 0));


		//Botones
		CreateWindow(L"button", L"I",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			1000, 100,
			20, 20,
			hWnd, (HMENU)BUTTON_START,
			hInst, NULL);

		CreateWindow(L"button", L"B",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1025, 100,
			20, 20,
			hWnd, (HMENU)BUTTON_BLOCK,
			hInst, NULL);

		CreateWindow(L"button", L"Start",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1050, 130,
			50, 20,
			hWnd, (HMENU)BUTTON_SEARCH,
			hInst, NULL);

		CreateWindow(L"button", L"Reset",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1000, 130,
			50, 20,
			hWnd, (HMENU)BUTTON_RESET,
			hInst, NULL);

		CreateWindow(L"button", L"0.5",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1050, 100,
			20, 20,
			hWnd, (HMENU)BUTTON_M05,
			hInst, NULL);
		CreateWindow(L"button", L"1",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			1075, 100,
			20, 20,
			hWnd, (HMENU)BUTTON_M1,
			hInst, NULL);
		break;
	}
	case WM_LBUTTONUP:
		iCordx = LOWORD(lParam) / iDivX;
		iCordy = HIWORD(lParam) / iDivY;
		if (iCordx < graphWidth && iCordy < graphWidth)
			switch (tool)
			{
			case SelectedTool::START:
				graphInicio = &nodes[iCordy + iCordx*graphWidth];
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::BLOCK:
				nodes[iCordy + iCordx*graphWidth].active = true;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::MWEIGHT:
				nodes[iCordy + iCordx*graphWidth].weight+= MEDIUM_WEIGHT;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::HWEIGHT:
				nodes[iCordy + iCordx*graphWidth].weight += HIGH_WEIGHT;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			default:
				break;
			}
		break;
	case WM_RBUTTONUP:
		iCordx = LOWORD(lParam) / iDivX;
		iCordy = HIWORD(lParam) / iDivY;
		if (iCordx < graphWidth && iCordy < graphWidth)
			switch (tool)
			{
			case SelectedTool::START:
				graphFinal = &nodes[iCordy + iCordx*graphWidth];
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::BLOCK:
				nodes[iCordy + iCordx*graphWidth].active = false;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::MWEIGHT:
				nodes[iCordy + iCordx*graphWidth].weight -= MEDIUM_WEIGHT;
				if (nodes[iCordy + iCordx*graphWidth].weight < 0)
					nodes[iCordy + iCordx*graphWidth].weight = 0;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case SelectedTool::HWEIGHT:
				nodes[iCordy + iCordx*graphWidth].weight -= HIGH_WEIGHT;
				if (nodes[iCordy + iCordx*graphWidth].weight < 0)
					nodes[iCordy + iCordx*graphWidth].weight = 0;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			default:
				break;
			}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
				//MENU ===========================
			case ID_PATHFINDING_BFS:
				walker = bfs;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_PATHFINDING_DFS:
				walker = dfs;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_PATHFINDING_BESTFS:
				walker = bestfs;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_PATHFINDING_DJIKSTRA:
				walker = djikstra;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_PATHFINDING_A:
				walker = astar;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_EURISTICA_EUCLIDEANA:
				actualEuristic = Heuristic::kEuclidean;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_EURISTICA_CUADRATICA:
				actualEuristic = Heuristic::kCuadratic;
				walker->SetHeuristic(actualEuristic);
				break;
			case ID_EURISTICA_MANHATTAN:
				actualEuristic = Heuristic::kManhatan;
				walker->SetHeuristic(actualEuristic);
				break;
				//BOTONES ==============================
			case BUTTON_START:
				tool = SelectedTool::START;
				break;
			case BUTTON_BLOCK:
				tool = SelectedTool::BLOCK;
				break;
			case BUTTON_RESET:
				for (auto &it : nodes)
				{
					it.active = true;
					it.weight = DEFAULT_WEIGHT;
					path.clear();
					bSearched = false;
					graphInicio = &nodes[0];
					graphFinal = &nodes[0];
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case BUTTON_SEARCH:
				path = walker->Search(graphInicio, graphFinal);
				closedList = walker->GetClosedList();
				walker->Reset();
				bSearched = true;
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			case BUTTON_M05:
				tool = SelectedTool::MWEIGHT;
				break;
			case BUTTON_M1:
				tool = SelectedTool::HWEIGHT;
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_SIZE:
		iAlto = HIWORD(lParam);
		iAncho = LOWORD(lParam);
		iDivY = iAlto / graphWidth;
		iDivX = iDivY;
		break;
    case WM_PAINT:
        {
			HBRUSH oldBr;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
			int id = 0;
			for (int y = 0; y< graphWidth; y++)
				for (int x = 0; x < graphWidth; x++)
				{
					Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
					if (!nodes[y + x * graphWidth].active)
					{
						oldBr = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(GRAY_BRUSH)));
						Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
						SelectObject(hdc, oldBr);
					}
					else
						if (nodes[y + x * graphWidth].weight > 10)
						{
							oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColorHW));
							Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
							SelectObject(hdc, oldBr);
						}
						else
							if (nodes[y + x * graphWidth].weight > 30)
							{
								oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColorMW));
								Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
								SelectObject(hdc, oldBr);
							}
					if (bSearched)
					{
						for (auto &it : closedList)
						{
							if (it->id == id)
							{
								oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColorClosed));
								Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
								SelectObject(hdc, oldBr);
								break;
							}
						}
						for (auto &it : path)
						{
							if (it->id == id)
							{
								oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColor));
								Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
								SelectObject(hdc, oldBr);
								break;
							}
						}

						id++;
					}
					if (&nodes[y+ x * graphWidth] == graphInicio)
					{
						oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColorBlue));
						Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
						SelectObject(hdc, oldBr);
					}else 
					if (&nodes[y + x * graphWidth] == graphFinal)
					{
						oldBr = static_cast<HBRUSH>(SelectObject(hdc, hColorRed));
						Rectangle(hdc, iDivX*x, iDivY*y, iDivX*(x + 1), iDivY*(y + 1));
						SelectObject(hdc, oldBr);
					}
					
				
				}
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

// Controlador de mensajes del cuadro Acerca de.
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
