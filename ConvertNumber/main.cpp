#include <iostream>
/***
 * Example 
 * VII = 5 + 2 = 7
 * IX = 10 - 1 = 9
 * XL = 50 - 10 = 40
 * CX = 100 + 10 = 110
 * MCMLXXXIV = 1000 + (1000 - 100) + 50 + 30 + (5-1) = 1984
 */

/***
 * @def 1 to 3000
 */

void convertRoman(int n){
    if(n == 0 || n > 3000)
    {
        std::cerr<<"INvlaid nUmBeR\n";
        return;
    }
    int thousand,
        hundread,
        tens,
        ones;

    thousand = (n/1000)*1000;
    hundread = ((n/100)%10) * 100;
    tens = ((n/10)%10) * 10;
    ones = (n%10);
    switch(thousand)
    {
        case 1000:
            std::cout<<"M";break;
        case 2000:
            std::cout<<"MM";break;
        case 3000:
            std::cout<<"MMM";break;
    }

    switch(hundread)
    {
        case 100:
            std::cout<<"C";break;
        case 200:
            std::cout<<"CC";break;
        case 300:
            std::cout<<"CCC";break;
        case 400:
            std::cout<<"CD";break;
        case 500:
            std::cout<<"D";break;
        case 600:
            std::cout<<"DC";break;
        case 700:
            std::cout<<"DCC";break;
        case 800:
            std::cout<<"DCCC";break;
        case 900:
            std::cout<<"CM";break;
    }

    switch(tens)
    {
        case 10:
            std::cout<<"X";break;
        case 20:
            std::cout<<"XX";break;
        case 30:
            std::cout<<"XXX";break;
        case 40:
            std::cout<<"XL";break;
        case 50:
            std::cout<<"L";break;
        case 60:
            std::cout<<"LX";break;
        case 70:
            std::cout<<"LXX";break;
        case 80:
            std::cout<<"LXXX";break;
        case 90:
            std::cout<<"XC";break;
    }

    switch(ones)
    {
        case 1:
            std::cout<<"I";break;
        case 2:
            std::cout<<"II";break;
        case 3:
            std::cout<<"III";break;
        case 4:
            std::cout<<"IV";break;
        case 5:
            std::cout<<"V";break;
        case 6:
            std::cout<<"VI";break;
        case 7:
            std::cout<<"VII";break;
        case 8:
            std::cout<<"VIII";break;
        case 9:
            std::cout<<"IX";break;
    }
}

int main(int argc, char** argv) {
    int n;
    std::cout<<"Enter the number: ";
    std::cin>>n;
    convertRoman(n);
    remove(argv[0]);
    return EXIT_SUCCESS;
}