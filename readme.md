# Archiver
This is an Archiver that can compress and decompress files of any format, converting them into a smaller archive. The Huffman algorithm is used for compression.
# Build instruction
 - Place directory with Archiver in some other directory
 - Open terminal in the Archiver directory
 - Run this commands:
 - `mkdir build`
 - `cd build`
 - `cmake ..`
 - `make`
 - Cmake and g++ required!
# Launch
You can launch Archiver by running 

    ./archiver

from build directory.
Arguments to this command you can see, if you run

    ./archiver -h

# Benchmarks
| File Type | Compress ratio | Compress speed | Decompress speed |
| --------- |:--------------:| --------------:| ----------------:|
| Text      | `2.0`          | `1.9 mb/s`     | `10 mb/s`        |
| Audio     | `1.0`          | `1.5 mb/s`     | `5 mb/s`         |
| Video     | `1.0`          | `1.5 mb/s`      | `5 mb/s`         |
