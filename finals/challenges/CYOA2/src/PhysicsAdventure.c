#include<stdio.h>

float constants[11] = {1.324717957,     // Plastic Number
                       3.8275e26,       // Solar Luminosity
                       0.0072973525664, // Fine Structure Constant
                       6.02214086e23,   // Avogadro
                       299792458,       // Speed of Light
                       1.38064852e-23,  // Boltzmann Constant
                       32.065,          // Mass of Sulfur
                       -0.0,
                       2.8977729e-3,    // Wein's constant
                       5.2917721067e-11,// Bohr Radius
                       8.314462175      // Ideal Gas constant
                       };

int floatToInt(const void* pointer){
    return *(int*)pointer;
}

void displayRoom(int position){
    if (position < 0){
        printf("You tried floating backwards, but for some reason, you cannot.\n\n");
        displayRoom(0);
        return;
    }

    else if (position > 10){
        printf("You tried floating forwards, but for some reason, you cannot.\n\n");
        displayRoom(10);
        return;
    }

    printf ("Your position: %d\n", position);
    printf ("As you float, the pointer on your instrument reads %u.\n", floatToInt(constants+position));

    printf("Where would you like to float?\n");
    printf("1 to float backwards.\n");
    printf("2 to float forwards.\n");
    printf("9 to float into the void. (Quit)\n");


    int choice;
    scanf("%d", &choice);

    if (choice == 1){
        printf("\n");
        displayRoom(position - 1);
    }
    else if (choice == 2){
        printf("\n");
        displayRoom(position + 1);
    }
    else if (choice == 9){
        printf("\n");
        return;
    }
    else {
        printf("Invalid Choice\n");
    }
}

int main(){
    setvbuf(stdin, NULL, _IONBF,0);
    setvbuf(stdout, NULL, _IONBF,0);

    displayRoom(0);
    printf("You close your instrument and your eyes as you float into the void.\n");
    printf("Goodbye, you're welcomed back again.\n");
    return 0;
}
