//โค้ดอันนี้อ่ะจะเล่นใน Terminal เลย เราไม่รู้นะว่าถ้าจะเอาไปใช้กับ unreal หรือ unity หรืออะไรได้มั้ย ยังไงก็เอาไว้เป็นตัวอย่างก่อนกะได้5555
#include <iostream> 
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

bool gameOver; //ตัวแปรนี้ไว้ใช้ปรับให้มันเป็น true กะ false ก็คือเกมจะเซ็ตไว้เป็นflaseก่อนแล้วถ้าเกิดเจออะไรที่ทำให้มันตายก็แค่เปลี่ยนตัวแปรนี้เป็นtrue เกมก็จะหยุด
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
int reverseDuration ; //อันนี้กะสถานะรีเวิร์สกี่เฟรม
bool fruitEat;
bool restart = false;
string fruit1;

void Setup() { //ฟังก์ชั่นนี้มีไว้เซ็ตค่าของตัวแปรต่างๆว่าตอนเริ่มจะให้ค่าอะไรเป็นยังไง
    gameOver = false; //อันนี้กะให้เป็นfalseไว้เกมจะได้ยังไม่จบ
    dir = STOP; //อันนี้คือให้ทิศทางเป็นstopจนกว่าผู้เล่นจะกดwsad
    x = width / 2; //x y คือตำแหน่งของงูในเฟรมนั้นๆ ตอนแรกเราจะให้มันเริ่มที่กลางจอเลยเอากว้างกะยาวมาหาร2
    y = height / 2;//^^
    score = 0;//อันนี้เอาไว้เก็บแต้มของคนเล่น
    fruitEat = true;
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
    nTail =0;
}
//GAMEOVER
void Rest(){
    system("cls");
for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านบน ที่ต้อเป็นwidth+2เป็นเพราะเราให้ข้างในที่งูวิ่งได้คือ20*20แล้วรั้วให้คลอบ20นั้นอีกทีมันเลยกลายเป็น22ช่อง
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) { // อันนี้คือการวาดพื้นที่ด้านใน20*20 i = แกน y ,j = แกนx
        for (int j = 0; j < width+2; j++) {
            if (j == 0)//อันนี้คือการวาดรั้วด้านซ้าย ไม่อยู่ในพื้นที่20*20เพราะเป็นฟังชั่นifคนละอันกัน
                cout << "#";
            else if(i == height/2 && j == (width/2)-3) cout << "G";
            else if(i == height/2 && j == (width/2)-2) cout << "A";
            else if(i == height/2 && j == (width/2)-1) cout << "M";
            else if(i == height/2 && j == (width/2)) cout << "E";
            else if(i == height/2 && j == (width/2)+1) cout << "O";
            else if(i == height/2 && j == (width/2)+2) cout << "V";
            else if(i == height/2 && j == (width/2)+3) cout << "E";
            else if(i == height/2 && j == (width/2)+4) cout << "R";
            else if (j == width + 1)//อันนี้คือการวาดรั้วด้านขวา ไม่อยู่ในพื้นที่20*20เพราะเป็นฟังชั่นifคนละอันกัน
                cout << "#";
            else if (j > 0 && j < width + 1)cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)//อันนี้คือวาดรั้วด้านล่าง
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
Sleep(100);
}

void generateFruit(){
    if(fruitEat){
    int gf = rand()%100+1;
    if(gf <= 30){
    fruitX = rand() % width;//ส่วนค่าพวกนี้คือการเซ็ตให้ตำแหน่งของผลไม้randomเกิดตามแกน x y
    fruitY = rand() % height;
    fruit1 = "fruit";
    }
    if(gf <= 50 && gf >30){
    boostFruitX = rand() % width;
    boostFruitY = rand() % height;
    fruit1 = "boost";
    }
    if(gf <=65 && gf > 50){
    poisonFruitX = rand() % width;
    poisonFruitY = rand() % height;
    fruit1 = "poison";
    }
    if (gf <=80 && gf > 65)
    {
    fatFruitX = rand() % width;
    fatFruitY = rand() % height;
    fruit1 = "fat";
    }
    if (gf <= 90 && gf > 80)
    {
    reverseFruitX = rand() % width;
    reverseFruitY = rand() % height;
    fruit1 = "reverse";
    }
    if (gf <= 100 && gf > 90)
    {
    MinusFruitX = rand() % width;
    MinusFruitY = rand() % height;
    fruit1 = "Minus";
    }
    }
}

void generateFruit2(){
    if(fruitEat){
    int gf = rand()%100+1;
    if(gf <= 30 && fruit1 != "fruit"){
    fruitX = rand() % width;//ส่วนค่าพวกนี้คือการเซ็ตให้ตำแหน่งของผลไม้randomเกิดตามแกน x y
    fruitY = rand() % height;
    }
    else if (gf <= 30 && fruit1 == "fruit")
    generateFruit2();
    

    if(gf <= 50 && gf >30 && fruit1 != "boost"){
    boostFruitX = rand() % width;
    boostFruitY = rand() % height;
    }
    else if (gf <= 50 && gf >30 && fruit1 == "boost")
    generateFruit2();
    

    if(gf <=65 && gf > 50 && fruit1 != "poison"){
    poisonFruitX = rand() % width;
    poisonFruitY = rand() % height;
    }
    else if (gf <=65 && gf > 50 && fruit1 == "poison")
    generateFruit2();
    

    if (gf <=80 && gf > 65 && fruit1 != "fat")
    {
    fatFruitX = rand() % width;
    fatFruitY = rand() % height;
    }
    else if (gf <=80 && gf > 65 && fruit1 == "fat") generateFruit2();

    if (gf <= 90 && gf > 80 && fruit1 != "reverse")
    {
    reverseFruitX = rand() % width;
    reverseFruitY = rand() % height;
    }
    else if (gf <= 90 && gf > 80 && fruit1 == "reverse") generateFruit2();

    if (gf <= 100 && gf > 90 && fruit1 != "Minus")
    {
    MinusFruitX = rand() % width;
    MinusFruitY = rand() % height;
    }
    else if(gf <= 100 && gf > 90 && fruit1 == "Minus") generateFruit2();

    fruitEat = false ;
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

void Input() {//ฟักชั่นนี้มีไว้รับinputในการเดิน wsadนั่นแหละะ
    if (_kbhit()) {//ไอ่_kbhit()เนี่ยหน้าที่ของมันคือการตรวจดูว่าคนเล่นได้กดคีย์บอร์ดมั้ย ถ้ากดก็เข้าคอนดิชั่น ถ้าไม่กดก็skipไป
        switch (_getch()) {//ไอ่_getch()คือการตรวจดูว่าสวิชที่คนเล่นกดคือสวิชอะไร
        //ไอ้พวกdir != RIGHT ,LEFT หรืออะไรเนี่ยเราใส่มาเพราไม่อยากให้งูมันเดินกลับหลัง180องศา เพราะมันจะชนหางตัวเองที่วิ่งมาตามมัน ก็เลยใส่ไว้ให้มันเดินได้แค่ซ้ายกะขวาของทางที่มันเดินอยู่
        case 'a'://ถ้ากดตัว a
            if (dir  !=RIGHT){//เช็คก่อนว่ามันเดินขวาอยู่รึเปล่าถ้า ไม่ใช่ ไปต่อ 
                if (isReversed && dir != LEFT) dir = RIGHT;//อันนี้คือผลไม้มึนมันจะทำให้งูเดินคนละทางกะที่สั่งก็เลยใส่บรรทัดนี้มาในกีณีที่มันมึนอยู่
                else dir = LEFT;//ถ้าไม่มึนก็ให้มันเดินไปซ้ายตามปกติ
            }
            break;
        case 'd':
            if (dir != LEFT ) {//เหมือนกันแค่เดินขวา
                if (isReversed && dir != RIGHT) dir = LEFT;
                else dir = RIGHT;
            }
            break;
        case 'w':
            if (dir != DOWN) {//เหมือนกันแค่เดินขึ้น
            if (isReversed && dir != UP) dir = DOWN;
                else dir = UP;
            }
            break;
        case 's':
            if (dir != UP){ //เหมือนกันแค่เดินลง
                if (isReversed && dir != DOWN) dir = UP;
                else dir = DOWN;
                }
            break;
        case 'x'://ปุมออกเกม กดxปุ๊บเกมจบเลย
            gameOver = true;
            break;
        }
    }
}

void Logic() {//(ฟังก์ชั่นเชี่ยย วุ่นวายชิบ555)ฟังก์ชั่นนี้คือฟังชั่นที่ใช้รันเกมทั้งหมด
    int prevX = tailX[0];//ส่วนของตรงนี้ถึงบรรทัดที่135เป็นการส่งค่าตำแหน่งของหัวให้หางอันที่1ในเฟรมต่อไป แล้วหางอันที่1ก็จะส่งตำแหน่งให้หางอันที่2 ต่อไปอีก อธิบายยาก ไว้ก่อนละกันน5555
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
        y--;//ไอ้นี่ก็ลงเรื่อยๆ
        break;
    case DOWN:
        y++;//ไอ้นี่ก็ขึ้นเรื่อยๆ
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
        fruitEat = true;
    }

    if (x == MinusFruitX && y == MinusFruitY){
        score -= 10;
        nTail--;
        fruitEat = true;
    }
    

    if (x == boostFruitX && y == boostFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลบูส จะทำให้งูเป็นงูspeed
        score += 20;//ได้scoreเพิ่ม
        isBoosted = true;//ตัวแปลที่บอกว่างูspeedอยู่เปล่ากลายเป็นtrue
        boostDuration = 20;//ระยะเฟรมที่อยากให้มันspeed
        fruitEat = true;     
    }

    if (x == poisonFruitX && y == poisonFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลไม้ที่เขียนโค้ดง่ายที่สุดในโลก ผลพิษ กินละตาย
        gameOver = true;//แค่นี้ก็ตายละ
    }

    if (x == fatFruitX && y == fatFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลอ้วน ทำให้งูยาวขึ้น2ช่อง
        score += 15;//ได้scoreเพิ่ม
        nTail += 2; // จำนวนหาง+2
        fruitEat = true;
    }

    if (x == reverseFruitX && y == reverseFruitY) {//ตรงนี้คือกรณีที่ตำแหน่งหัวทับกะตำแหน่งผลมึน  ทำให้งูเดินกลับด้าน
        score += 30;//ได้scoreเพิ่ม
        isReversed = true;//ตัวแปลที่บอกว่างูมึนอยู่เปล่ากลายเป็นtrue
        reverseDuration = 30;//ระยะเฟรมที่อยากให้มันมึน
        fruitEat = true;
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
     if (fruitEat)
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

void GameOver() {
    cout << "Game Over! Press R to Restart or X to Exit." << endl;
    while (true) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == 'r' || choice == 'R') {
                Setup();
                return;
            } else if (choice == 'x' || choice == 'X') {
                restart = true;
                return;
            }
        }
    }
}

int main() {//เกมมีแค่นี้แหละะ
srand(time(0));
    Setup();//ยัดฟังก์ชั่นsetเข้าไป กำหนดค่าของตัวแปรต่างๆ
    while(!restart){
    while (!gameOver) {//gameOverเป็นfalseอยู่ก็เล่นต่อไปป
        Draw();//สร้างmapขึ้นใหม่ในทุกๆเฟรม
        generateFruit();
        generateFruit2();
        Input();//รับinputเพื่อเดินในทุกๆเฟรม
        Logic();//ทำงานตามinputละกะLogicของเกม
        //Sleepคือการกำหนดความเร็วเฟรมยิงเฟรมผ่านไปเร็ว(ก็คือค่าในSleepยิ่งน้อย)งูก็จะดูเหมือนวิ่งไวขึ้นเท่านั้น
        if (isBoosted)//เช็คว่างูspeedอยู่ป่าว
            Sleep(20); // ถ้าspeedอยู่เพิ่มความเร็วของเฟรม
        else
            Sleep(100); // ถ้าไม่speedแล้ว ก็กลับมาความเร็วเฟรมปกติ
    }
    Rest();
    GameOver();
    }
    return 0;
}