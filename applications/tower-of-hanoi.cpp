#include <iostream>

void towerOfHanoi(int k, char source, char dest, char temp) {
    if (k == 1) {
        std::cout << "Move one disk from " << source << " to " << dest << std::endl;
        return;
    }

    towerOfHanoi(k - 1, source, temp, dest); // Move k-1 disks to temp
    towerOfHanoi(1, source, dest, temp);     // Move 1 disk to dest
    towerOfHanoi(k - 1, temp, dest, source); // Move k-1 to dest
}

int main() {
    towerOfHanoi(5, 'rod_A', 'rod_B', 'rod_C');
    return 0;
}
