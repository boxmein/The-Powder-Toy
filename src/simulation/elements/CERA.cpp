#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CERA PT_CERA 177

Element_CERA::Element_CERA()
{
    Identifier = "DEFAULT_PT_CERA"; 
    Name = "CERA"; 
         
    Colour = PIXPACK(0xFF6138); 
    MenuVisible = 1; 
    MenuSection = SC_SOLIDS; 
    Enabled = 1; 
    
    Advection = 0.0f; 
    AirDrag = 0.00f * CFDS; 
    AirLoss = 0.90f; 
    Loss = 0.00f; 
    Collision = 0.0f; 
    Gravity = 0.0f; 
    Diffusion = 0.00f; 
    HotAir = 0.000f  * CFDS; 
    Falldown = 0; 
    
    Flammable = 0; 
    Explosive = 0; 
    Meltable = 0; 
    Hardness = 0; 
    
    Weight = 100; 
    
    Temperature = R_TEMP+273.15f; 
    HeatConduct = 150; 
    Description = "Ceramics! "; 
    
    State = ST_SOLID; 
    Properties = TYPE_SOLID | PROP_HOT_GLOW | PROP_NEUTPASS; 
    
    

    LowPressure = -30.0f; 
    LowPressureTransition = PT_CLST; // breaks into CLST under -30 pressure 
    HighPressure = IPH; 
    HighPressureTransition = NT; 
    LowTemperature = ITL; 
    LowTemperatureTransition = NT; 
    HighTemperature = 4273.15f; // melts at 4000 deg C.
    HighTemperatureTransition = PT_LAVA; 
    
    Update = &Element_CERA::update; 
    Graphics = &Element_CERA::graphics; 
}

//#TPT-Directive ElementHeader Element_CERA static int update(UPDATE_FUNC_ARGS)
// #define UPDATE_FUNC_ARGS Simulation* sim, int i, int x, int y, int surround_space, int nt, Particle *parts, int pmap[YRES][XRES]
int Element_CERA::update(UPDATE_FUNC_ARGS) 
{
  int rx, ry, r; 

  for (ry=-1; ry<=1; ry++) {
    for (rx=-1; rx<=1; rx++) {
      if (BOUNDS_CHECK && (rx || ry) && pmap[y+ry][x+rx]) {

        r = pmap[y+ry][x+rx];
        
        if ((r&0xFF) == PT_PROT)
          sim->kill_part(r);
      }
    }
  }

}


//#TPT-Directive ElementHeader Element_CERA static int graphics(GRAPHICS_FUNC_ARGS)
int Element_CERA::graphics(GRAPHICS_FUNC_ARGS) 
{
  return 0;
}

Element_CERA::~Element_CERA() {}