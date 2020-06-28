#include "Common/logging.h"

#include "RealEngine.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
	RealEngine r;
	r.run();
	return 0;
}
