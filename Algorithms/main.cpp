#include <iostream>
#include <string>
#include <vector>


#include <filesystem>
namespace fs = std::filesystem;

#include "BinarySearch.hpp"
#include "FibonnaciSearch.hpp"
#include "Sort.hpp"
#include "CountProblems.hpp"
#include "Formatting.hpp"
#include "StringProcessing.hpp"

#include "Linux.hpp"
#include "Bitmap.hpp"
#include "Blur.hpp"
#include "Polynomial.hpp"
#include "FileIO.hpp"
#include "CollectionTypes.hpp"
#include "Graph.hpp"

#include "OpenGL.hpp"
#include "OpenGL_v2.h"
#include "triangle.hpp"
#include "Assets.hpp"
#include "RandomInputGenerator.hpp"

#include "DistributedSelfStabilizingAlgorithms.hpp"
#include "CLI.hpp"
#include "MeasureUnits.hpp"
#include "NumberTheory.hpp"
#include "FileLoaderBMP.hpp"
#include "VAO_VBO.hpp"

#include "Prime.hpp"
#include "Dts.hpp"
#include "KinematicEngine.hpp"
#include "MultiThreaded.hpp"
#include "Async.hpp"

int main(int argc, char** argv) {
// test OpenGL
//    StartGL_v1();
//    StartGL_v2();
//    Info_v2();

//    Start_Triangle_v1(argc, argv);
//    Collatz_v1(12);

//    CLI_v1(argc, argv);


//    Texture texture;
//    texture.LoadImageBitmap("/img/king_white.bmp");
//
//    uint32_t number = 1235;
//    Uint32_t2 num = DecomposeIntoWidthAndHeight_v1(number);
//    std::cout << "decompose " << number << " into " << num.x << " and " << num.y << " such that x * y = " << num.x * num.y << "\n";
//    std::string file_header_BMP =   "4d42 bef2 0015 0000 0000 008a 0000 007c"
//                                    "0000 02ee 0000 01db 0000 0001 0020 0003"
//                                    "0000 be68 0015 0000 0000 0000 0000 0000"
//                                    "0000 0000 0000 0000 00ff ff00 0000 00ff"
//                                    "0000 0000 ff00 4742 7352 c280 28f5 b860"
//                                    "151e 8520 01eb 3340 1333 6680 2666 6640"
//                                    "0666 99a0 0999 0a3c 03d7 5c24 328f";
//    std::cout << "number of bytes: " << CountHexBytesInString(file_header_BMP) << "\n";
//
//    Bitmap_v2 bitmap = LoadBMP("img/Vector.bmp");
//    LoadBMPIntoOpenGL(bitmap);
//
//    _v2::initContext(argc, argv);

//    std::string file = v2::LoadFile("./CommonComplications");
//    file = v2::LoadFile("/CommonComplications");
//    file = v2::LoadFile("CommonComplications");
//    file = v2::LoadFile(".../CommonComplications");
//    std::cout << "file:\n" << file << "\n";

//    v2::Graphics graphics;
//    graphics.mainLoop();

//    for(int i = 0; i < 100; i++)
//        std::cout << "prime: " << NextPrime() << "\n";
//    std::cout << "u32_squares: " << u32_squares() << "\ncubes: " << u64_cubes() << "\n";

//    Uint a {}, b{};
//    uint32_t value_a[] {3123456789, 3123456789, 3123456789, 3123456789};
//    uint32_t value_b[] {3123456789, 3123456789, 3123456789, 3123456789};
//    a.value = value_a;
//    a.count = sizeof(value_a) / sizeof(uint32_t);
//    b.value = value_b;
//    b.count = sizeof(value_b) / sizeof(uint32_t);
//    Uint c = a + b;                                       // seems to work somewhat
//    for(uint64_t idx {0}; idx < c.count; idx++) {
//        std::cout << c.value[idx] << " ";
//    }   std::cout << "\n";
//    Particle_2Dim a {7.0, 5.0, 1.0};
//    Particle_2Dim b {3.0, 7.0, 1.0};
//    Collide_2Body_v1(a, b);
//
//    for(uint64_t idx{0}; idx < 1000; idx++) {
//        std::cout << "mersenne[" << idx << "]: " << NextMersennePrime() << "\n";
//    }

//    IsPrime_distributed_v1(1111111111111111111);

//    test1(1000000001);
//    playground::testPlayground3(1, 10000000, 8);

    async_playground::playground_v1();
}


