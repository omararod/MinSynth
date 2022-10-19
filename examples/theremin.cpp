#include "BodyApp.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLn, int nCmdShow)
{
	CBodyBasics app;
	return app.Run(hInst, nCmdShow);
}