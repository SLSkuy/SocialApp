// 2023051604044 万睿
// 2024-12-23
// ui动画交互实现

#include "socialui.h"
#include "netizen.h"

#include <iostream>
#include <unistd.h> //for usleep()
#include <string>

void clearScreen()  //清空屏幕
{
    std::cout << "\033[2J\033[H";
}

void loadingAnimation() //加载动画
{
    clearScreen();  //清屏确保软件占据整个终端增加交互体验
    std::cout << "Yuzu-ChatPlatform is loading:\n";
    int total_steps{30}; // 动画步骤总数
    for (int i = 0; i <= total_steps; ++i) {
        // 使用回车符\r将光标移到行首，然后输出更新的内容
        std::cout << "\rProgress: [";

        // 输出进度条的部分
        int progress = (i * 50) / total_steps;  // 计算进度条的填充比例
        for (int j = 0; j < 50; ++j) {
            if (j < progress) {
                std::cout << "#";  // 填充进度
            } else {
                std::cout << " ";  // 空白区域
            }
        }

        std::cout << "] " << (i * 100) / total_steps << "%";

        drawFrame(i);    //绘制ciallo

        for(int i = 0;i < 2;i++)std::cout << "\033[A";  //光标上移

        usleep(100000);  // 暂停100ms，用来模拟动画的进度
    }
    for(int i = 0;i < 2;i++)std::cout << "\033[B";  //光标下移
    std::cout << std::endl;

    drawCat();
    std::cout << "你可以看小猫！" << std::endl;
    std::cout << "done!" << std::endl;
    usleep(1500000);

    clearScreen(); //清屏确保软件占据整个终端增加交互体验
}

void drawFrame(const int& frame) {
    const char* cat_frames[] = {
        R"(
Ciallo～(∠・ω< )⌒/
    )",
        R"(
Ciallo～(∠・ω< )⌒|
    )",
        R"(
Ciallo～(∠・ω< )⌒\
    )",
        R"(
Ciallo～(∠・ω< )⌒-
    )",
        R"(
Ciallo～(∠・ω< )⌒★
    )"
    };

    std::cout << cat_frames[frame % 5]; //5帧循环
}

void drawCat()
{
    std::cout << R"(

                             kOOOOOO
                          kO0OO000OOOOOkx
                         k000K0KXXXKK0OOOOkxd
                        xOKKKXK0XNNNNNXXK0OOOkdol
                       xk0KXXXXKKXNNNNNNXK0OO00Oxollc
                       kOKKXXXXXXKXXNNNXKXNNX0O00OOxo:::
                       O0KKXXXXKKKXNNNNNXXNWWNX00O0Oxoodx
                      0OKKKKXK0KXNNNNNNNNNNWNNXKOOOOkkkkkxo     dddooooool           kkkkkkkk
                      xOKK0KXXKKKKKKKXNXXNNXK000000OOOOkddxkkxkkkkxxxxddoolldxxxxkkkkOOOOkkkxc
                      x0K00XXXXXXKO0XNNX00KK00000000OOkxxkkOkkO00000OkkxkkxoloxxdkKXKKKKKK0kko;
                       0K0KXXXXXX00XXKKKKKKKKKK00000OkxkOOOkxxkkkkkOOOkkkOOxdloxkxkKXK00KOkkk
                       0KKKXXXXKK0KK00KKKKKKKKKKK000kkOOOOOkxxkOkkkkkkkkkkkkkxooxkkxkOOOOOOOxl;
                       00KKKXKKK000OO0KKKKKK000000OkkOOOOOOkxkOOOOkOOOkkkkOOkkkdoxkkkOkkOOOOd:;
                  dxxxOO0KKK0000OOO00000000OO000OkkOOOOOOOkkkOOOkkOOOkkkOOOkkkkddkkkkkkOOOko;;
                ooooxkxxOO000OOOkkkOOOOOOOOOkOOOOxxkOOOOOOkkkkOOOkkOOOkkkkkkkxxkkxxkkkxxOOOxc;
              olllloxOOkkOOO0OOOkxkkkkOOkkkkkkOOkxdxkOkOOOkkxxkOOkkkkOkkkkkOkkxxkkkxxkkxxkOkl;
            loooolldkOkkOOOOOOOkxxkkkkkOOOOOO00OkddkkOOOOOOkodkkOOOkkkkkkkkOkxodkkkxxkkxdxko:;,
             dddddodxkkkkOkkOOOkxxkxxkkkO0000000OxdxkO0000OkxodkkO00OkkOOkkkkkxloxkOkxxxxxdolc
            dddxxxxkxkkkkkkkkxdxxxxkkkOOkkkOOkkxdxkOOOO0OxxxxxkO0000000OOkkOklldkkOkxxkOxollll
            xxxxdxkxxkxxxxxxxxkxxxxxxdxxxxxkkOOkkxdkOOkkOOkxk0kxkk00OOOOOO00O0kdooxkOOxxxOOdlllcc
          ddoddxddddoddddxxkkkxxkkkkxxxxxkkOOOkxxdxOkkkkkxxO0kxkkOkkxxxkkOOO0kxkxdkkkxdxkOdccccc
         ddxkkkkxxo  ldxxxkkkxxkkkOkxxxxxxxxxxxdxkxkkkkkxdkOOxxkkkxkkkkxxxxkOkdxxdxkkxdxxxocccccc
       OOO0Okkkkoc   oxkkkkkdxOOOkxxkkxxxkkOkxxOOkkkkkxxkKXXOxkkxxkkkkkkkxxkxdxkdxkkxdxxdocccccc
      00000kkOkl     dOOOOkxdxOOOkxdkkxxkkkkkkk0OkkkkkdkKXXX0xkkxxxkkkkkkkkkxdOXOxxkxdxkxollcccc
   O000000OO0klc     oOOOOxddxkOOkdxkkkkkkkkkxkXKxxxkxx0XXXXOxxxddxxxkkkxxkkxdOXKkxxdoxkxolccccc
  OOOOOOOOOOOdc      lk0OkdddxkkOkdxkkkkkkkkkxOXKkdxxdk0KKXKkdxdodxxxxxxddxkddOKXOddooxkxocccccc
 OOOkkkkkkkkko:      lk0OkdddxkkOkdxkkkkkkkkkxddollolclooodkkddkOkdddxxdodxxolxkOOxoloxkxocccc
odkkkkkkkkkkkdc      ck0kxddddkOOkddkkkkkkkkkxlc        llx000KXK0Okxddddddc    cccldkkxoccccc
cldxxkxxxxxxxdo      lOOkxdxkxxOOkddkkkkkkkkkdlcc       o0XXXXXXXKKXKK000dc     ooccldkkxoccccc
cccodxxxxxxdddooc    oOOkddkOxdxOOdoxkkkkkkkkdllc       dKNXXXXXXXKKXXXXKd     oKX0doxkkxdlcccc
ccclllooollokxooo    xOOkdxkkkxdxOxoxkkkkkkkkxolc      cOXXXXXXXXXXXXXXXXkc    dKKOooxkkxddlccc
lloolcccc:lkOdoxdc  lO0OkdxOOkkdoxxodxkOOkkkkkOkocc   lOXXXXXXXXXXXXXXXXXKxc  cOX0dloxkkxdxo
       ccc;ldocldoc;;okkkxdxkkxxddxdddxkOOOOkkk0XKOOkkOKXXXXXXXXXXXXXXXXXXXKOooOKKklodxkkkdxdc)" << std::endl;
}
