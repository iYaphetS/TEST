#include <stdio.h>
#include "/usr/include/idna.h"

int main() {
	return idna_to_ascii_8z(NULL, NULL, 0);
}
