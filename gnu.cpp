//โค้ดอันนี้อ่ะจะเล่นใน Terminal เลย เราไม่รู้นะว่าถ้าจะเอาไปใช้กับ unreal หรือ unity หรืออะไรได้มั้ย ยังไงก็เอาไว้เป็นตัวอย่างก่อนกะได้5555
#include <iostream> 
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

bool gameOver; //ตัวแปรนี้ไว้ใช้ปรับให้มันเป็น true กะ false ก็คือเกมจะเซ็ตไว้เป็นflaseก่อนแล้วถ้าเกิดเจออะไรที่ทำให้มันตายก็แค่เปลี่ยนตัวแปรนี้เป็นtrue เกมก็จะข้ามwhile loop ของระบบเกมทั้งหมดไป
bool restart = true;//ตัวแปรนี้จะเป็นตัวแปรที่อยู่ในwhile loop ที่ครอบwhile loop ของgameOverไว้อีกที เอาไว้สำหรับปุ่มเริ่มใหม่
const int width = 20; // -->> width กะ height มีไว้กำหนดขอบของเกมไม่ให้งูเดินเลยขอบ 
const int height = 20; // ----^^
int x, y, fruitX, fruitY,MinusFruitX,MinusFruitY, boostFruitX, boostFruitY, poisonFruitX, poisonFruitY, fatFruitX, fatFruitY, reverseFruitX, reverseFruitY, score;
// ^^บรรทัดบนนี้กำหนดตัวแปรส่วนใหญ่คือการระบุตำแหน่งของผลไม้แต่ละชนิดกะตัวงูยกเว้นscoreที่เอาไว้เก็บแต้มของคนเล่น
int tailX[200], tailY[200]; //สองอันนี้มีไว้เก็บว่าตอนนี้งูมีกี่หางแล้ว
int nTail; // อันนี้คือตัวแปรที่จะเพิ่มขึ้นถ้างูกินผลไม้เอาไว้ใส่แบบนี้ tailX[nTail](อันนี้แค่ประมาณนะเดี๋ยวข้างในจริงๆจะเป็นตัวk)
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //อันนี้กำหนดทิศเอาไว้สำหรับให้งูเดิน 
eDirection dir; //อันนี้ก็คืออันบน^นั่นแหละะแค่ทำให้สั้นลง555
bool isBoosted = false; //อันนี้เอาไว้สำหรับผลไม้บูสความเร็ว มันจะคล้ายๆgameOver คือเราจะกำหนดมันเป็นtrue กะ false ถ้าเกิดงูกินผลนี้กะให้ค่านี้เป็นtrue แล้วมันก็จะเข้าคอนดิชั่นif
bool isReversed = false;//อันนี้เหมือนอันบนเลย แค่เป็นของผลรีเวิร์ส
int boostDuration ; //อันนี้คือตัวแปรที่จะบอกว่างูจะได้เราสถานะบูสกี่เฟรม
int reverseDuration ;  //อันนี้กะสถานะรีเวิร์สกี่เฟรม
bool fruitEat;//อันนี้เป็นตัวแปรที่จะบอกว่างูกินผลไม้ยัง มีไว้สำหรับระบบที่ผลไม้จะโผล่แค่2ผลแบบสุ่ม(ตอนแรกกะเลยไม่มี555)
string fruit1;//อันนี้คือเราไม่อยากให้ผลไม้2ผลที่ranมามันเป็นผลเดียวกันเลยมีตัวแปรนี้สำหรับบอกว่าผลไม้อันที่1คือผลอะไร
 bool STA = false;

void Setup() { //ฟังก์ชั่นนี้มีไว้เซ็ตค่าของตัวแปรต่างๆว่าตอนเริ่มจะให้ค่าอะไรเป็นยังไง
    gameOver = false; //อันนี้กะให้เป็นfalseไว้เกมจะได้ยังไม่over
    dir = STOP; //อันนี้คือให้ทิศทางเป็นstopจนกว่าผู้เล่นจะกดwsad
    x = width / 2; //x y คือตำแหน่งของงูในเฟรมนั้นๆ ตอนแรกเราจะให้มันเริ่มที่กลางจอเลยเอากว้างกะยาวมาหาร2
    y = height / 2;//^^
    score = 0;//อันนี้เอาไว้เก็บแต้มของคนเล่น
    fruitEat = true;//อันนี้เพราะเราอยากให้มันสุ่มขึ้นมา2ผลเลยก็เลยเซ็ทเป็นtrue
    fruitX = 21;//ตั้งแต่บรรทัดนี้(32)จนถึงบรรทัดที่43 เราจะเซ็ทค่าของผลไม้ต่างๆให้เป็น21ไว้ก่อน ส่วนของที่วาดผลไม้จะรันถึงแค่20เลยทำให้ผลไม้ทุกผลยังไม่ถูกวาด
    fruitY = 21;//       ^
    poisonFruitX =21;//  ^
    poisonFruitY =21;//  ^
    MinusFruitX = 21;//  ^
    MinusFruitY = 21;//  ^
    boostFruitX = 21;//  ^
    boostFruitY = 21;//  ^
    fatFruitX =21 ;//    ^
    fatFruitY = 21;//    ^
    reverseFruitX =21;// ^
    reverseFruitY =21;// ^
    nTail =0;//อันนี้คือเราจะเซ็ทnTailกลับเป็น0ทุกคั้งที่restart
}

void start(){
        system("cls");//ลบหน้าเก่าในทุกๆเฟรม
for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านบน
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) { // อันนี้คือการวาดพื้นที่ด้านใน20*20 i = แกน y ,j = แกนx
        for (int j = 0; j < width+2; j++) {
            if (j == 0)//อันนี้คือการวาดรั้วด้านซ้าย
                cout << "#";
            else if(i == (height/2)-1 && j == (width/2)-4) cout << "S";//ไอ่พวกนี้คือวาดคำว่าGAMEOVERมาตรงกลางของตาราง
            else if(i == (height/2)-1 && j == (width/2)-3) cout << "N";//^
            else if(i == (height/2)-1 && j == (width/2)-2) cout << "A";//^
            else if(i == (height/2)-1 && j == (width/2)-1) cout << "K";//^
            else if(i == (height/2)-1 && j == (width/2)) cout << "E";//^
            else if(i == (height/2)-1 && j == (width/2)+2) cout << "G";//^
            else if(i == (height/2)-1 && j == (width/2)+3) cout << "A";//^
            else if(i == (height/2)-1 && j == (width/2)+4) cout << "M";//^
            else if(i == (height/2)-1 && j == (width/2)+5) cout << "E";//^
            else if (j == width + 1)//อันนี้คือการวาดรั้วด้านขวา 
                cout << "#";
            else if (j > 0 && j < width + 1)cout << " ";//วาดช่องว่างตรงที่ไม่มีอะไร
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านล่าง
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;//โชว์แต้มscore
Sleep(100);//กำหนดความเร็วเฟรม

}

void Gamesta(){
    cout << "Press H to Start or X to Exit." << endl;
    while (! STA) {//เราต้องการให้loopนีรันอยู่ตลอดในตอนที่gameOverไปแล้วเลยเซ็ทเป็นwhile(true)
        if (_kbhit()) {//ถ้ามีการกดปุ่ม
            char choice = _getch();//choice = ปุ่มที่กด
            if (choice == 'H' || choice == 'h') {//ถ้าปุ่มที่กดเป็นr
                STA = true;//เซ็ทเกมใหม่
                break;
            } else if (choice == 'x' || choice == 'X') {//ถ้าปุ่มที่กดเป็นx
                gameOver = true;
                restart = false;//ออกเกม
                break;
            }
        }
    }
}

void Draw() {  // อันนี้เป็นฟังก์ชั่นที่จะวาดmapของเกมขึ้นมา
    system("cls"); //บรรทัดนี้คือการทำให้ terminal มันลบหน้าเก่าออกก่อนที่จะสร้างหน้าใหม่ขึ้นมา เลยเกิดภาพเป็นframeๆแบบดูง่ายๆ
    for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านบน ที่ต้อเป็นwidth+2เป็นเพราะเราให้ข้างในที่งูวิ่งได้คือ20*20แล้วรั้วให้คลอบ20นั้นอีกทีมันเลยกลายเป็น22ช่อง
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) { // อันนี้คือการวาดพื้นที่ด้านใน20*20 i = แกน y ,j = แกนx
        for (int j = 0; j < width; j++) {
            if (j == 0)//อันนี้คือการวาดรั้วด้านซ้าย ไม่อยู่ในพื้นที่20*20เพราะเป็นฟังชั่นifคนละอันกัน
                cout << "#";
    //-----------------------------------------------------
            if (i == y && j == x)//อันนี้คือการเช็คว่าตอนนี้เรารันจนถึงจุดที่หัวงูอยู่รึยังถ้าใช้ให้พิมพ์Oที่เป็นหัวงูตรงนั้นออกมา
                cout << "O";
            else if (i == fruitY && j == fruitX)//อันนี้วาดผลไม้ธรรมดา
                cout << "F";
            else if (i == boostFruitY && j == boostFruitX)//อันนี้วาดผลไม้บูส
                cout << "B";
            else if (i == poisonFruitY && j == poisonFruitX)//อันนี้วาดผลไม้พิษ
                cout << "P";
            else if (i == fatFruitY && j == fatFruitX)//อันนี้วาดผลไม้ตัว+2
                cout << "A";
            else if (i == reverseFruitY && j == reverseFruitX)//อันนี้วาดผลไม้มึน
                cout << "R";
            else if (i == MinusFruitY && j == MinusFruitX)
                cout << "M";
            else {  //อันนี้คือถ้ามันตั้งแต่บรรทัดที่51ถึง61แล้วไม่ตรงเลยให้พิมพ์หางไม่ก็" "
                bool printtail = false;//ตรงนี้เราจะเซ็ตตัวแปรสำหรับบอกไอ่สเปสบาร์ว่าเห้ยกูปริ้นหางละนะ ไม่ต้องปริ้นสเปสอีกตัว
                for (int k = 0; k < nTail; k++) { //อันนี้คือเช็คว่าตอนนี้งูมีกี่หางจะได้ปริ้นหางออกมาตามนั้น
                    if (tailX[k] == j && tailY[k] == i) {//ตรงนี้คเช็คว่าจุดที่โปรแกรมรันถึงใช่ตำแหน่งของหางมั้ยถ้าใช่ให้ปริ้นoละเปลี่ยนprinttailเป็นtrue
                        cout << "o";
                        printtail = true;
                    }
                }
                if (!printtail)//ตรงนี้มีไว้ปริ้นสเปสบาร์ถ้ามันไม่ได้ปริ้นหาง ถ้ามันปริ้นหางตรงนี้จะกลายเป็นfalseแล้วจะskipไป
                    cout << " ";
            }
    //----------------------------------------------------
            if (j == width - 1)//อันนี้คือการวาดรั้วด้านขวา ไม่อยู่ในพื้นที่20*20เพราะเป็นฟังชั่นifคนละอันกัน
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านล่าง
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;//อันนี้เอาไว้โชว์score
}

void Rest(){//ฟังก์ชั่นนี้มีไว้วาดหน้าGAMEOVER มันจะคล้ายๆฟังก์ชั่นDrawเลย
    system("cls");//ลบหน้าเก่าในทุกๆเฟรม
for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านบน
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) { // อันนี้คือการวาดพื้นที่ด้านใน20*20 i = แกน y ,j = แกนx
        for (int j = 0; j < width+2; j++) {
            if (j == 0)//อันนี้คือการวาดรั้วด้านซ้าย
                cout << "#";
            else if(i == height/2 && j == (width/2)-3) cout << "G";//ไอ่พวกนี้คือวาดคำว่าGAMEOVERมาตรงกลางของตาราง
            else if(i == height/2 && j == (width/2)-2) cout << "A";//^
            else if(i == height/2 && j == (width/2)-1) cout << "M";//^
            else if(i == height/2 && j == (width/2)) cout << "E";//^
            else if(i == height/2 && j == (width/2)+1) cout << "O";//^
            else if(i == height/2 && j == (width/2)+2) cout << "V";//^
            else if(i == height/2 && j == (width/2)+3) cout << "E";//^
            else if(i == height/2 && j == (width/2)+4) cout << "R";//^
            else if (j == width + 1)//อันนี้คือการวาดรั้วด้านขวา 
                cout << "#";
            else if (j > 0 && j < width + 1)cout << " ";//วาดช่องว่างตรงที่ไม่มีอะไร
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านล่าง
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;//โชว์แต้มscore
Sleep(100);//กำหนดความเร็วเฟรม
}

void generateFruit(){//ฟังก์ชั่นนี้เป็นฟังก์ชั่นสำหรับกำหนดผลไม้ลูกที่1ขึ้นมา
    if(fruitEat){//ถ้าเกิดว่างูกินผลไม้ไม่ว่าจะผลอะไร fruitEat = true แล้วก็จะเข้าเงื่อนไขนี้
    int gf = rand()%100+1;//สุ่มค่าขึ้นมาค่านึงตั้งแต่1->100
    if(gf <= 30){//ถ้าค่าที่สุ่มมาน้อยกว่าหรือเท่ากับ30(30%)
    fruitX = rand() % width;//เซ็ตให้ตำแหน่งของผลไม้ปกติrandomเกิดตามแกน x y
    fruitY = rand() % height;//^
    fruit1 = "fruit";//กำหนดให้ตัวแปรfruit1เป็นผลไม้ธรรมดา
    }
    if(gf <= 50 && gf >30){//เหมือนกันเลยแต่เป็นของผลไม้speed (20%)
    boostFruitX = rand() % width;
    boostFruitY = rand() % height;
    fruit1 = "boost";
    }
    if(gf <=65 && gf > 50){//เหมือนกันเลยแต่เป็นของผลไม้พิส(15%)
    poisonFruitX = rand() % width;
    poisonFruitY = rand() % height;
    fruit1 = "poison";
    }
    if (gf <=80 && gf > 65)//เหมือนกันเลยแต่เป็นของผลไม้อ้วน(15%)
    {
    fatFruitX = rand() % width;
    fatFruitY = rand() % height;
    fruit1 = "fat";
    }
    if (gf <= 90 && gf > 80)//เหมือนกันเลยแต่เป็นของผลไม้มึน(10%)
    {
    reverseFruitX = rand() % width;
    reverseFruitY = rand() % height;
    fruit1 = "reverse";
    }
    if (gf <= 100 && gf > 90)//เหมือนกันเลยแต่เป็นของผลไม้ลบ(10%)
    {
    MinusFruitX = rand() % width;
    MinusFruitY = rand() % height;
    fruit1 = "Minus";
    }
    }
}

void generateFruit2(){//หลังจากกำหนดผลไม้1ขึ้นมาแล้วก็จะมาที่ฟังก์ชั่นนี้เพื่อกำหนดผลไม้2 (ทำงานเหมือนกันเลยแค่มีการเช็คว่าผลไม้ซ้ำรึเปล่า)
    if(fruitEat){//หลังจากสร้างผลไม้1 ในฟังก์ชั่นของผลไม้1ยังไม่ได้เปลี่ยน fruitEat ให้เป็นfalse เพราะงั้นก็จะรันตรงนี้ต่อได้เลย
    int gf = rand()%100+1;//สุ่มค่าขึ้นมาค่านึงเหมือนเดิม
    if(gf <= 30 && fruit1 != "fruit"){//ถ้าgfน้อยกว่าเท่ากับ30 เช็คว่าผลไม้1ใช่ผลปกติมั้ยถ้าไม่ใช่สร้างผลปกติ
    fruitX = rand() % width;
    fruitY = rand() % height;
    }
    else if (gf <= 30 && fruit1 == "fruit")//ถ้าผลไม้1เป็นผลปกติ
    generateFruit2();//สุ่มผล2ใหม่
    

    if(gf <= 50 && gf >30 && fruit1 != "boost"){//เหมือนกันเลยแต่เป็นของผลไม้speed
    boostFruitX = rand() % width;
    boostFruitY = rand() % height;
    }
    else if (gf <= 50 && gf >30 && fruit1 == "boost")
    generateFruit2();
    

    if(gf <=65 && gf > 50 && fruit1 != "poison"){//เหมือนกันเลยแต่เป็นของผลไม้พิษ
    poisonFruitX = rand() % width;
    poisonFruitY = rand() % height;
    }
    else if (gf <=65 && gf > 50 && fruit1 == "poison")
    generateFruit2();
    

    if (gf <=80 && gf > 65 && fruit1 != "fat")//เหมือนกันเลยแต่เป็นของผลไม้อ้วน
    {
    fatFruitX = rand() % width;
    fatFruitY = rand() % height;
    }
    else if (gf <=80 && gf > 65 && fruit1 == "fat") generateFruit2();

    if (gf <= 90 && gf > 80 && fruit1 != "reverse")//เหมือนกันเลยแต่เป็นของผลไม้มึน
    {
    reverseFruitX = rand() % width;
    reverseFruitY = rand() % height;
    }
    else if (gf <= 90 && gf > 80 && fruit1 == "reverse") generateFruit2();

    if (gf <= 100 && gf > 90 && fruit1 != "Minus")//เหมือนกันเลยแต่เป็นของผลไม้ลบ
    {
    MinusFruitX = rand() % width;
    MinusFruitY = rand() % height;
    }
    else if(gf <= 100 && gf > 90 && fruit1 == "Minus") generateFruit2();

    fruitEat = false ;//ถ้าสุ่มผลที่2เสร็จเปลี่ยนfruitEat เป็น false
    }  

}

void Input() {//ฟังก์ชั่นนี้มีไว้รับinputในการเดิน wsadนั่นแหละะ
    if (_kbhit()) {//ไอ่_kbhit()เนี่ยหน้าที่ของมันคือการตรวจดูว่าคนเล่นได้กดคีย์บอร์ดมั้ย ถ้ากดก็เข้าคอนดิชั่น ถ้าไม่กดก็skipไป
        char choice = _getch(); //ไอ่_getch()คือการตรวจดูว่าสวิชที่คนเล่นกดคือสวิชอะไร
        //ไอ้พวกdir != RIGHT ,LEFT หรืออะไรเนี่ยเราใส่มาเพราไม่อยากให้งูมันเดินกลับหลัง180องศา เพราะมันจะชนหางตัวเองที่วิ่งมาตามมัน ก็เลยใส่ไว้ให้มันเดินได้แค่ซ้ายกะขวาของทางที่มันเดินอยู่
        if(choice == 'a' or choice == 'A'){//ถ้ากดตัว a
            if (dir  !=RIGHT){//เช็คก่อนว่ามันเดินขวาอยู่รึเปล่าถ้า ไม่ใช่ ไปต่อ 
                if (isReversed && dir != LEFT) dir = RIGHT;//อันนี้คือผลไม้มึนมันจะทำให้งูเดินคนละทางกะที่สั่งก็เลยใส่บรรทัดนี้มาในกรณีที่มันมึนอยู่
                else dir = LEFT;//ถ้าไม่มึนก็ให้มันเดินไปซ้ายตามปกติ
            }
        }
        if(choice == 'd' or choice == 'D'){
            if (dir != LEFT ) {//เหมือนกันแค่เดินขวา
                if (isReversed && dir != RIGHT) dir = LEFT;
                else dir = RIGHT;
            }
        }
        if(choice == 'w' or choice == 'W'){
            if (dir != DOWN) {//เหมือนกันแค่เดินขึ้น
            if (isReversed && dir != UP) dir = DOWN;
                else dir = UP;
            }
        }
            if(choice == 's' or choice == 'S'){
            if (dir != UP){ //เหมือนกันแค่เดินลง
                if (isReversed && dir != DOWN) dir = UP;
                else dir = DOWN;
                }
            }
        if(choice == 'x' or choice == 'X'){//ปุ่มออกเกม กดxปุ๊บเกมจบเลย
            gameOver = true;
        }
    }
}

void Logic() {//(ฟังก์ชั่นเชี่ยย วุ่นวายชิบ555)ฟังก์ชั่นนี้คือฟังชั่นที่ใช้รันเกมทั้งหมด
    int prevX = tailX[0];//ส่วนของตรงนี้ถึงบรรทัดที่267เป็นการส่งค่าตำแหน่งของหัวให้หางอันที่1ในเฟรมต่อไป แล้วหางอันที่1ก็จะส่งตำแหน่งให้หางอันที่2 ต่อไปอีก อธิบายยาก ไว้ก่อนละกันน5555
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {//ที่เราบอกว่าพอรับwsadมาแล้วให้มันเดินซ้ายขวา จริงมันจะมาเดินเอาตรงนี้นี่แหละ
    case LEFT://ในเคสที่ไดเรคชั่นเป็น LEFT ก็ให้ตำแหน่งในแกนxของหัวงูขยับไปทางซ้ายเรื่อยๆ
        x--;
        break;
    case RIGHT:
        x++;//ไอ้นี่ก็ขวาเรื่อยๆ
        break;
    case UP:
        y--;//ไอ้นี่ก็ขึ้นเรื่อยๆ
        break;
    case DOWN:
        y++;//ไอ้นี่ก็ลงเรื่อยๆ
        break;
    default:
        break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;//สองบรรทัดนี้คือทำให้เวลางูมันหลุดขอบมันจะกลับมาจากอีกฝั่ง โดยการเซ็ทค่าตำแหน่งของ x ให้กลับมาเป็น 0 หรือwidth - 1
    if (y >= height) y = 0; else if (y < 0) y = height - 1;//^ y ให้กลับมาเป็น 0 หรือheight - 1

    for (int i = 0; i < nTail; i++)//ตรงนี้คือการเช็คว่าตำแหน่งของหางชนกะตำแหน่งของหัวรึเปล่า ถ้าชน เซ็ทgameOverเป็นtrue
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลไม้ธรรมดา
        score += 10;//ได้scoreเพิ่ม
        nTail++;//จำนวนหางบวก1
        fruitEat = true;//เปลี่ยนfruitEat = trueให้มันไปเข้าเงื่อนไขของgeneratefruit
    }

    if (x == MinusFruitX && y == MinusFruitY){//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลไม้ลบ
        score -= 10;//scoreลด10
        nTail--;//หางลดลง1
        fruitEat = true;//เปลี่ยนfruitEat = trueให้มันไปเข้าเงื่อนไขของgeneratefruit
        if(nTail == 0)gameOver = true;
    }
    

    if (x == boostFruitX && y == boostFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลบูส จะทำให้งูเป็นงูspeed
        score += 20;//ได้scoreเพิ่ม
        isBoosted = true;//ตัวแปลที่บอกว่างูspeedอยู่เปล่ากลายเป็นtrue
        boostDuration = 20;//ระยะเฟรมที่อยากให้มันspeed
        fruitEat = true;//เปลี่ยนfruitEat = trueให้มันไปเข้าเงื่อนไขของgeneratefruit
    }

    if (x == poisonFruitX && y == poisonFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลไม้ที่เขียนโค้ดง่ายที่สุดในโลก ผลพิษ กินละตาย
        gameOver = true;//แค่นี้ก็ตายละ
        //ไม่ต้องเปลี่ยนfruitEatเป็นtrueเพราะมันตายอยู่ละะ
    }

    if (x == fatFruitX && y == fatFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลอ้วน ทำให้งูยาวขึ้น2ช่อง
        score += 15;//ได้scoreเพิ่ม
        nTail += 2; // จำนวนหาง+2
        fruitEat = true;//เปลี่ยนfruitEat = trueให้มันไปเข้าเงื่อนไขของgeneratefruit
    }

    if (x == reverseFruitX && y == reverseFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลมึน  ทำให้งูเดินกลับด้าน
        score += 30;//ได้scoreเพิ่ม
        isReversed = true;//ตัวแปลที่บอกว่างูมึนอยู่เปล่ากลายเป็นtrue
        reverseDuration = 30;//ระยะเฟรมที่อยากให้มันมึน
        fruitEat = true;//เปลี่ยนfruitEat = trueให้มันไปเข้าเงื่อนไขของgeneratefruit
    }

    if (isBoosted) {//อันนี้คือการลดเฟรมที่เราเซ็ทเลงไปเรื่อยๆเพื่อสร้างระยะเวลาที่จะทำให้งูกลับมาเป็นปกติ ใน1เฟรมโค้ดรัน1ครั้ง ถ้างูspeedอยู่
        boostDuration--;//ลดค่าเฟรมที่อยากให้speedลง1
        if (boostDuration == 0) {//ถ้าเกิดเฟรมเหลือ0
            isBoosted = false;//งูไม่speedละ
        }
    }

    if (isReversed) {//ทำงานเหมือนกันกับงูspeedแต่เป็นของผลมึน
        reverseDuration--;
        if (reverseDuration == 0) {
            isReversed = false;
        }
    }
     if (fruitEat)//อันนี้คือในกรณีที่งูกินผลไม้ ให้ลบผลทุกผลออกไปก่อน ถ้าไม่มีตรงนี้มันก็จะมีโอกาศที่ผลเดิมจะยังไม่หายแต่สร้างผลใหม่มาแล้วว
    {
    fruitX = 21;
    fruitY = 21;
    poisonFruitX =21;
    poisonFruitY =21;
    MinusFruitX = 21;
    MinusFruitY = 21;
    boostFruitX = 21;
    boostFruitY = 21;
    fatFruitX =21 ;
    fatFruitY = 21;
    reverseFruitX =21;
    reverseFruitY =21;
    }
     
}

void GameOver() {//ฟังก์ชั่นนี้คือปุ่มrestart
    cout << "Game Over! Press R to Restart or X to Exit." << endl;
    while (true) {//เราต้องการให้loopนีรันอยู่ตลอดในตอนที่gameOverไปแล้วเลยเซ็ทเป็นwhile(true)
        if (_kbhit()) {//ถ้ามีการกดปุ่ม
            char choice = _getch();//choice = ปุ่มที่กด
            if (choice == 'r' || choice == 'R') {//ถ้าปุ่มที่กดเป็นr
                Setup();//เซ็ทเกมใหม่
                return;//กลับไปเริ่มloopด้านบนใหม่
            } else if (choice == 'x' || choice == 'X') {//ถ้าปุ่มที่กดเป็นx
                restart = false;//ออกเกม
                return;
            }
        }
    }
}

int main() {//เกมมีแค่นี้แหละะ
srand(time(0));
    Setup();//ยัดฟังก์ชั่นsetเข้าไป กำหนดค่าของตัวแปรต่างๆ
    while(restart){//ถ้าคนเล่นยังไม่กดออกก็วนต่อไปป
    start();
    Gamesta();
    while (!gameOver) {//gameOverเป็นfalseอยู่ก็เล่นต่อไปป
        Draw();//สร้างmapขึ้นใหม่ในทุกๆเฟรม
        generateFruit();//สร้างผลไม้1ทุกครั้งที่กิน
        generateFruit2();//สร้างผลไม้2ทุกครั้งที่กิน
        Input();//รับinputเพื่อเดินในทุกๆเฟรม
        Logic();//ทำงานตามinputละกะLogicของเกม
        //Sleepคือการกำหนดความเร็วเฟรมยิงเฟรมผ่านไปเร็ว(ก็คือค่าในSleepยิ่งน้อย)งูก็จะดูเหมือนวิ่งไวขึ้นเท่านั้น
        if (isBoosted)//เช็คว่างูspeedอยู่ป่าว
            Sleep(20); // ถ้าspeedอยู่เพิ่มความเร็วของเฟรม
        else
            Sleep(100); // ถ้าไม่speedแล้ว ก็กลับมาความเร็วเฟรมปกติ
    }
    Rest();//วาดGAMEOVER
    GameOver();//รอดูว่าคนเล่นจะrestartหรือออก
    }
    return 0;
}