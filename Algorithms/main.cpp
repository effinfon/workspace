#include <iostream>
#include <string>
#include <vector>

//#include "KnowledgeBase.hpp"
//#include "Crypto.hpp"
#include "GraphAlgorithms.hpp"

//#include <sys/signal.h>
//#include <unistd.h>

//#include "Async.hpp"
//#include "HeteroType.hpp"
//#include "VersionControl.hpp"
//#include "Graphics.hpp"
//#include "Decomposition.hpp"
//#include "Games.hpp"
//#include "SFML.hpp"
//#include "ChatNetwork.hpp"
//#include "Games.hpp"
//#include "Library.hpp"
//#include "Files.hpp"
//#include "Editor.hpp"
//#include "SFML_Utilitary.hpp"
//#include "MeasureUnits.hpp"

//#include "LabWork.hpp"
//#include "MultiThreaded.hpp"
//#include "Hash.hpp"

//#include "Dts.hpp"
//#include "TreeDTS.hpp"
//#include "QueueDTS.hpp"
//#include "IDE.hpp"
//#include "RandomInputGenerator.hpp"
//#include "Graph.hpp"
/*
template <typename T>
T max(T a, T b) {
    return b < a ? a : b;   // (*?) supposedly there is a good reason for this symmetry, which is ... ?
}

int* getExpired() {
    struct A { int* bla; A() { bla = new int(1234); } ~A() { std::cout << "bla: " << *bla << "\n"; // delete bla;
    }};
    A a;
    return a.bla;
}
*/

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

//    async_playground::playground_v1();
//    async_playground::playground_v2();

//    kill(getpid(), SIGABRT);

//    int32_t original_bitmaski {0b1000000000000000000000000};
//    uint32_t original_bitmaskui {0b1000000000000000000000000};
//    for(uint8_t idx {0}; idx < 64; idx++) {
//        std::cout << "int: " << original_bitmaski << " uint: " << original_bitmaskui << "\n";
//        original_bitmaskui >> 1;
//        original_bitmaski >> 1;
//    }

//    uint64_t initial[64] {123, 456, 789, 012, 345, 678, 901, 234, 567, 890};
//    ConwayLife life1 {initial};
//    life1.TerminalPrint();
//    printf("\n");
//    life1.NextStateSpace();
//    life1.TerminalPrint();

/// TD
//    SFML::main();

/// TD
//    Chat::Server server;
//
//    Chat::Client client1;
//    client1.Connect("127.0.0.1", 12345);
//    Chat::Client client2;
//    client2.Connect("localhost", 12345);
//    client1.Run();

/// TD
//    Games::RPG rpg;
//    rpg.Run();

/// TD
//    Editor editor;
//    LimitedLifetime();
//    std::this_thread::sleep_for(std::chrono::seconds(2));

/// TD
//    ReallocatingArray<int>::DebugTest();
//    Graph::DebugTest();

/// TD
//    SFMLMultiThreading::test1();

/// TD
//    std::cout << Utilitary::leftrotate(1234, 0) << std::endl; // works fine
//    std::cout << Utilitary::leftrotate(1234, 1) << std::endl;
//    std::cout << Utilitary::leftrotate(1234, 2) << std::endl;
//    std::cout << Utilitary::leftrotate(1234, 3) << std::endl;

//    uint32_t block_hashes[5] {0x01234567, 0xFEDCBA98, 0xFEDCBA98, 0x76543210, 0xF0E1D2C3};    // displays fine
//    HashPlayground::SHA160Bit sha1 = HashPlayground::SHA160Bit(block_hashes);

/// TD
//    if(argc > 1) {
//        std::string project {argv[1]}; std::cout << project << "\n";
//        if(argc > 2) {
//            IDE::AddFileToProject(project, IDE::GetFiles(true, std::string {argv[2]}));
//    }   }   // (*?) this would be an interesting style

/// TD
//    system("PAUSE");

/// TD
//    int  i =42;
//    std::cout << "max: " << ::max(7,i) << '\n'; // ineteresting usage of the "::", (!?) it seems to signify "use the global namespace"
                // the "::" is likely used to explicitate the usage of the max() defined in the global state and not the one in std::
/// TD
//    int* a = getExpired();
//    std::cout << "expired, but alive -> leaked:" << *a << "\n";
//        // conslusion: (*?) there is nothing special about new-delete; they do not occur automatically at the end
//        // of scopes; they need to be manually handled in ctor and dtor (preferably there; and in any internal
//        // methods, which preferably do not get "exposed to the outside")

/// TD
//    RandomData data {};
//    std::string string {"integer64.20, unsigned32.7, byte.8, integer16.100, float64.9"};
//    uint64_t expectedBytes = 20 * 8 + 7 * 4 + 8 * 1 + 100 * 2 + 9 * 8;
//    void* bytes = data.ParseLanguageString_Language_v1(string);
//
//    printf("integer64:\n");
//    uint64_t offsetInBytes {0};
//    for(int i = 0; i < 20; i++) {
//        printf("%ld ", (int64_t*)(&((uint8_t*)(bytes))[offsetInBytes])[i]);
//    } printf("\n\n");
//
//    printf("unsigned32:\n");
//    offsetInBytes += 20 * 8;
//    for(int i = 0; i < 7; i++) {
//        printf("%u ", (uint32_t*)(&((uint8_t*)(bytes))[offsetInBytes])[i]);
//    } printf("\n\n");
//
//    printf("byte:\n");
//    offsetInBytes += 7 * 4;
//    for(int i = 0; i < 8; i++) {
//        printf("%u ", (uint8_t*)(&((uint8_t*)(bytes))[offsetInBytes])[i]);
//    } printf("\n\n");
//
//    printf("integer16:\n");
//    offsetInBytes += 8 * 1;
//    for(int i = 0; i < 100; i++) {
//        printf("%d ", (int16_t*)(&((uint8_t*)(bytes))[offsetInBytes])[i]);
//    } printf("\n\n");
//
//    printf("float64:\n");
//    offsetInBytes += 100 * 2;
//    for(int i = 0; i < 9; i++) {
//        printf("%lf ", (double*)(&((uint8_t*)(bytes))[offsetInBytes])[i]);
//    } printf("\n\n");

/// TD
//    Filter(GetAllFiles("/home/nq/"));

/// TD
//    Solve(3, 11, 7, 5);
//    printf("\n");
//    Solve(5, 11, 3, 9);
//    printf("\n");
//    Solve(7, 11, 17, 8);
//    printf("\n");
//    Solve(11, 13, 11, 7);
//    printf("\n");
//    Solve(17, 31, 7, 2);
//    printf("\n");

/// TD
    GraphAlgo::Graph_Conn conn;
    conn.AddEdge(-2, 3);
    conn.AddEdge(-2, 4);
    conn.AddEdge(-2, 2);
    conn.AddEdge(-2, 1);
    conn.AddEdge(-2, 0);
    conn.AddEdge(-1, 2);
    conn.AddEdge(-1, -3);
    conn.AddEdge(-1, 3);
    for(auto iter : conn.edges) {
        std::cout << iter.first << " " << iter.second << "\n";
    }
}


