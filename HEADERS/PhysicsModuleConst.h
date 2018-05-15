#pragma once

namespace PHYSICSCONST {
	const unsigned targetFPS = 200;
	const double targetFrameTime= (1.0 / static_cast<double>(targetFPS))*1000000.0;
	const double G = 10.0;
}