#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "interface.h"

int main (void) {
	//do some shit like try to index the path in config
	//maybe add some checks here to prevent the user from fucking shit up
	checkConfig();
	launch();

}
