/****************************************************************************
 *      This is part of the libYafaRay package
 *      Copyright (C) 2006  Mathias Wein
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "light/light.h"
#include "light/light_sun.h"
#include "light/light_spot.h"
#include "light/light_sphere.h"
#include "light/light_point.h"
#include "light/light_area.h"
#include "light/light_background.h"
#include "light/light_background_portal.h"
#include "light/light_directional.h"
#include "light/light_ies.h"
#include "light/light_meshlight.h"
#include "common/param.h"
#include "common/logger.h"

BEGIN_YAFARAY

std::unique_ptr<Light> Light::factory(Logger &logger, ParamMap &params, const Scene &scene)
{
	if(logger.isDebug())
	{
		logger.logDebug("**Light");
		params.logContents(logger);
	}
	std::string type;
	params.getParam("type", type);
	if(type == "arealight") return AreaLight::factory(logger, params, scene);
	else if(type == "bgPortalLight") return BackgroundPortalLight::factory(logger, params, scene);
	else if(type == "meshlight") return MeshLight::factory(logger, params, scene);
	else if(type == "bglight") return BackgroundLight::factory(logger, params, scene);
	else if(type == "directional") return DirectionalLight::factory(logger, params, scene);
	else if(type == "ieslight") return IesLight::factory(logger, params, scene);
	else if(type == "pointlight") return PointLight::factory(logger, params, scene);
	else if(type == "spherelight") return SphereLight::factory(logger, params, scene);
	else if(type == "spotlight") return SpotLight::factory(logger, params, scene);
	else if(type == "sunlight") return SunLight::factory(logger, params, scene);
	else return nullptr;
}

END_YAFARAY
