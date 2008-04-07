//@(#) To backup and restore ciphered disc's and partition's image
// Author: Andrew Wingorodov <http://andr.mobi/>
// Licence: GPLv3
// $Id$

#include <fstream>

#include <libcxx/iron.h>
#include <libcxx/er.h>
#include <libcxx/logostream.hpp>
#include <libcxx/timeter.h>

#include "buffer.hpp"

using namespace std;
using namespace cxx;
using namespace env;

static ssize_t BLK_SIZE = 512;

int
 main (
	  int argc
	, char** argv
) {
	ti::meter total ("work time (sec): ");
try {
	env::iron.getopt (argc, argv, "b:i:o:s:q");
	if ( !iron.exists ("i")) iron ["i"] = "/dev/hda"; ///< Input file
	if ( !iron.exists ("o")) iron ["o"] = "/tmp/img.bak"; ///< Output file
	if ( !iron.exists ("s")) iron ["s"] = "private.x509"; ///< Key name
	/// Set block size (512 by default)
	if ( iron.exists ("b")) BLK_SIZE = ::strtoul (iron("b").c_str(), 0, 10);

	obuffer bak ( iron ("o").c_str());
	ibuffer buf ( iron ("i"), BLK_SIZE);

	while ( buf.read ())
		bak.write (buf, buf.size());
	
} catch (const er::no& e) {
	logs << error << e.what() << endl;

} catch (const std::exception& e) {
	logs << error << e.what() << endl;
}

}
