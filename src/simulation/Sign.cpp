#include "Sign.h"
#include "graphics/Graphics.h"
#include "simulation/Simulation.h"

sign::sign(std::string text_, int x_, int y_, Justification justification_):
	x(x_),
	y(y_),
	ju(justification_),
	text(text_)
{
}

std::string sign::getText(Simulation *sim)
{
	char buff[256];
	char signText[256];
	sprintf(signText, "%s", text.substr(0, 255).c_str());

	if(signText[0] && signText[0] == '{')
	{
		if (!strcmp(signText,"{p}"))
		{
			float pressure = 0.0f;
			if (x>=0 && x<XRES && y>=0 && y<YRES)
				pressure = sim->pv[y/CELL][x/CELL];
			sprintf(buff, "Pressure: %3.2f", pressure);  //...pressure
		}
		else if (!strcmp(signText,"{t}"))
		{
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Temp: %4.2f", sim->parts[sim->pmap[y][x]>>8].temp-273.15);  //...temperature
			else
				sprintf(buff, "Temp: 0.00");  //...temperature
		}
		else if (!strcmp(signText,"{life}")) {
			// life
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Life: %d", sim->parts[sim->pmap[y][x]>>8].life);
			else
				sprintf(buff, "Life: -");
		}
		else if (!strcmp(signText,"{tmp}")) {
			// TMP
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Tmp: %d", sim->parts[sim->pmap[y][x]>>8].tmp);
			else
				sprintf(buff, "Tmp: -");
		}
		else if (!strcmp(signText,"{tmp2}")) {
			// TMP2
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Tmp2: %d", sim->parts[sim->pmap[y][x]>>8].tmp2);
			else
				sprintf(buff, "Tmp2: -");
		}
		else if (!strcmp(signText,"{vx}")) {
			// X velocity
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Vx: %d", sim->parts[sim->pmap[y][x]>>8].vx);
			else
				sprintf(buff, "Vx: -");
		}
		else if (!strcmp(signText,"{vy}")) {
			// Y velocity
			if (x>=0 && x<XRES && y>=0 && y<YRES && sim->pmap[y][x])
				sprintf(buff, "Vy: %d", sim->parts[sim->pmap[y][x]>>8].vy);
			else
				sprintf(buff, "Vy: -");
		}
		else if (!strcmp(signText,"{edgeMode}")) {
			sprintf(buff, "Edge Mode: %d", sim->edgeMode);
		}
		else if (!strcmp(signText,"{gravityMode}")) {
			sprintf(buff, "Gravity Mode: %d", sim->gravityMode);
		}
		else if (!strcmp(signText,"{legacyMode}")) {
			sprintf(buff, "Legacy Mode: %d", sim->legacy_enable);
		}
		else if (!strcmp(signText,"{ambientHeat}")) {
			sprintf(buff, "Ambient Heat: %d", sim->aheat_enable);
		}
		else if (!strcmp(signText,"{waterEqual}")) {
			sprintf(buff, "Water Equalisation: %d", sim->water_equal_test);
		}
		else if (!strcmp(signText,"{paused}")) {
			sprintf(buff, "Paused: %d", sim->sys_pause);
		}
		else if (!strcmp(signText,"{prettyPowder}")) {
			sprintf(buff, "Pretty powders: %d", sim->pretty_powder);
		}
		else if (!strcmp(signText,"{fighters}")) {
			sprintf(buff, "Fighters: %d", sim->fighcount);
		}
		else
		{
			int pos = splitsign(signText);
			if (pos)
			{
				strcpy(buff, signText+pos+1);
				buff[strlen(signText)-pos-2]=0;
			}
			else
				strcpy(buff, signText);
		}
	}
	else
	{
		strcpy(buff, signText);
	}

	return std::string(buff);
}

void sign::pos(std::string signText, int & x0, int & y0, int & w, int & h)
{
	w = Graphics::textwidth(signText.c_str()) + 5;
	h = 15;
	x0 = (ju == 2) ? x - w :
	      (ju == 1) ? x - w/2 : x;
	y0 = (y > 18) ? y - 18 : y + 4;
}

int sign::splitsign(const char* str, char * type)
{
	if (str[0]=='{' && (str[1]=='c' || str[1]=='t' || str[1]=='b' || str[1]=='s'))
	{
		const char* p = str+2;
		// signs with text arguments
		if (str[1] == 's')
		{
			if (str[2]==':')
			{
				p = str+4;
				while (*p && *p!='|')
					p++;
			}
			else
				return 0;
		}
		// signs with number arguments
		if (str[1] == 'c' || str[1] == 't')
		{
			if (str[2]==':' && str[3]>='0' && str[3]<='9')
			{
				p = str+4;
				while (*p>='0' && *p<='9')
					p++;
			}
			else
				return 0;
		}

		if (*p=='|')
		{
			int r = p-str;
			while (*p)
				p++;
			if (p[-1] == '}')
			{
				if (type)
					*type = str[1];
				return r;
			}
		}
	}
	return 0;
}
