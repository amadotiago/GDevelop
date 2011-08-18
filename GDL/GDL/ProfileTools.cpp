/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#if defined(GD_IDE_ONLY)

#include "ProfileTools.h"
#include "GDL/ProfileEvent.h"
#include "GDL/RuntimeScene.h"
#include "GDL/BaseProfiler.h"
#include <iostream>

void GD_API StartProfileTimer(RuntimeScene & scene, unsigned int id)
{
    scene.profiler->profileEventsInformation[id].Reset();
}

void GD_API EndProfileTimer(RuntimeScene & scene, unsigned int id)
{
    scene.profiler->profileEventsInformation[id].Stop();
}

#endif
