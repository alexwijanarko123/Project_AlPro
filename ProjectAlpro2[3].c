#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXI 100
#define MAXO 500
#define MENU "menu.txt"
#define ORDERS "orders.txt"

// Structure menu yang terdiri atas id, nama, harga, dan stok menu
struct Item{
    int id;
    char name[50];
    float price;
    int stock;
};
// Structure pesanan yang terdiri atas id pesanan, id menu, kuantitas, total harga, dan tanggal pesanan
struct Order{
    int orderID;
    int itemID;
    int quantity;
    float totalPrice;
    char date[20];
};

// Variabel global
struct Item menu[MAXI];
struct Order orders[MAXO];
int menuCount = 0;
int orderCount = 0;
float tot = 0.0;

// Function untuk login
int loginAsAdmin(){
    char username[50], password[50];
    printf("Masukkan username: "); 
    scanf("%s", username); // Meminta username
    printf("Masukkan password: ");
    scanf("%s", password); // Meminta password
    
    // Jika username dan password sesuai, maka user login sebagai admin
    if (strcmp(username, "ADMIN") == 0 && strcmp(password, "ADMIN123") == 0){ 
        printf("Login berhasil sebagai admin.\n");
        return 1;
    } 
	else {
        printf("Login berhasil sebagai customer.\n");
        return 0;
    }
}

// Function untuk menunjukkan menu yang ada
void displayMenu(){
	int i;
	// Jika tidak ada menu, maka akan langsung dikembalikan
    if (menuCount == 0){
        printf("Tidak ada menu!\n");
        return;
    }
    
    // Jika ada menu, maka akan langsung ditunjukkan menunya
    printf("\nBuku Menu\n");
    printf("ID\tName\t\tPrice\tStock\n");
    for (i = 0; i < menuCount; i++){
        printf("%d\t%-15s%.2f\t%d\n", 
               menu[i].id, 
               menu[i].name, 
               menu[i].price, 
               menu[i].stock);
    }
}

// Function untuk menambahkan menu
void addMenu(){
	// Jika jumlah menu melebihi jumlah maksimal menu, maka akan dikembalikan
    if (menuCount >= MAXI){
        printf("Tidak dapat menambahkan menu lagi!\n");
        return;
    }
    
    // Menambahkan menu dengan data terkait
    struct Item newItem; // Membuat structure Item untuk menu baru
    printf("Masukkan ID menu: ");
    scanf("%d", &newItem.id);
    printf("Masukkan nama menu: ");
    scanf(" %[^\n]s", newItem.name);
    printf("Masukkan harga menu(Rp): ");
    scanf("%f", &newItem.price);
    printf("Masukkan stok menu yang ada: ");
    scanf("%d", &newItem.stock);
    menu[menuCount++] = newItem;
    printf("Menu baru telah ditambahkan!\n");
}

// Function untuk mengubah data menu yang ada 
void editMenu(){
	int i;
    int id, found = 0; // Variabel found sebagai penanda apakah menu ditemukan atau tidak
    printf("Masukkan ID menu yang ingin diubah : "); 
    scanf("%d", &id); // ID menu yang ingin diubah
    for (i = 0; i < menuCount; i++){ // Looping untuk mencari menu yang ingin diubah
        if (menu[i].id == id){
            found = 1;
            printf("Mengedit menu: \n");
            printf("Masukkan nama menu: ");
            scanf(" %[^\n]s", menu[i].name);
            printf("Masukkan harga menu: ");
            scanf("%f", &menu[i].price);
            printf("Masukkan stok menu: ");
            scanf("%d", &menu[i].stock);
            printf("Menu berhasil diperbarui!\n");
            break;
        }
    }
    if (!found) {
        printf("Menu tidak ditemukan!\n");
    }
}

// Function untuk menghapus menu yang ada 
void deleteMenu(){
    int i, j;
    int id, found = 0; // Variabel found sebagai penanda apakah menu ditemukan atau tidak
    printf("Masukkan ID menu yang ingin dihapus: ");
    scanf("%d", &id); //ID menu yang ingin dihapus
    for (i = 0; i < menuCount; i++){ // Looping untuk mencari menu yang ingin dihapus
        if (menu[i].id == id){
            found = 1;
            for (j = i; j < menuCount - 1; j++){ //Looping untuk menggeser posisi menu
                menu[j] = menu[j + 1];
            }
            menuCount--;
            printf("Menu berhasil dihapuskan!\n");
            break;
        }
    } 
    if (!found){
        printf("Menu tidak ditemukan!\n");
    }
}

// Function untuk mengorder makanan atau minuman
void order(){
	int i;
	char x[2];
    if (menuCount == 0){
        printf("Tidak ada menu!\n");
        return;
    }
    struct Order newOrder; // Membuat structure untuk pesanan baru
    printf("Masukkan ID pesanan: ");
    scanf("%d", &newOrder.orderID);
    rep:
    printf("Masukkan ID menu: ");
    scanf("%d", &newOrder.itemID);
    printf("Masukkan kuantitas menu: ");
    scanf("%d", &newOrder.quantity);
    if (newOrder.quantity <= 0){
    	printf("Kuantitas harus lebih besar dari 0!\n");
    	return;
	}
    printf("Masukkan tanggal (DD/MM/YYYY): ");
    scanf(" %[^\n]s", newOrder.date);
    // Looping untuk mencari menu yang dipesan dan mengecek apakah stoknya masih tersedia, serta memperbarui data menu setelah pemesanan
    for (i = 0; i < menuCount; i++){
        if (menu[i].id == newOrder.itemID){
            if (menu[i].stock >= newOrder.quantity){
                newOrder.totalPrice = menu[i].price * newOrder.quantity;
				tot += newOrder.totalPrice;
                menu[i].stock -= newOrder.quantity;
                orders[orderCount++] = newOrder;
                printf("Apakah Anda ingin memesan lagi (Y/T) : ");
                scanf("%s", &x);
                if (strcmp(x, "Y") == 0){
                	goto rep;
				}
                printf("Pemesanan berhasil! Total: %.2f\n", tot);
                return;
            } 
			else {
                printf("Stok tidak mencukupi!\n");
                return;
            }
        }
    }
    printf("Menu tidak ditemukan!\n");
}

// Function untuk menampilkan pesanan yang ada
void displayOrders(){
	int i;
    if (orderCount == 0){
        printf("Tidak ada pesanan!\n");
        return;
    }
    printf("\nPesanan\n");
    printf("Order ID\tItem ID\tQuantity\tTotal\t\tDate\n");
    for (i = 0; i < orderCount; i++){
        printf("%d\t\t%d\t%d\t\t%.0f\t%s\n",
               orders[i].orderID,
               orders[i].itemID,
               orders[i].quantity,
               orders[i].totalPrice,
               orders[i].date);
    }
}

// Function untuk mengedit pesanan
void editOrder(){
    int neworderID, newQuantity, i;
    char newDate[20];
    int found = 0; // Sebagai penanda apakah pesanan ditemukan
    printf("Masukkan ID pesanan yang ingin diubah: ");
    scanf("%d", &neworderID); // ID pesanan yang ingin diubah
    
	// Mencari pesanan berdasarkan ID
    for (i = 0; i < orderCount; i++){
        if (orders[i].orderID == neworderID){
            found = 1;
            printf("Mengedit pesanan: \n");
            printf("Masukkan kuantitas baru: ");
            scanf("%d", &newQuantity);
            if (newQuantity <= 0){
                printf("Kuantitas harus lebih besar dari 0!\n");
                return;
            }
            printf("Masukkan tanggal baru (DD/MM/YYYY): ");
            scanf(" %[^\n]s", newDate);
            
            // Memperbarui pesanan
            orders[i].quantity = newQuantity;
            orders[i].totalPrice = newQuantity * menu[orders[i].itemID].price;  // Update total price sesuai kuantitas baru
            strcpy(orders[i].date, newDate);
            printf("Pesanan berhasil diperbarui!\n");
            return;
        }
    }
    if (!found){
        printf("Pesanan tidak ditemukan!\n");
    }
}

// Function untuk menghapus pesanan
void deleteOrder(){
    int delorderID, found = 0;
    int i, j;
    printf("Masukkan ID pesanan yang ingin dihapus: ");
    scanf("%d", &delorderID); // ID pesanan yang ingin dihapus
    
    // Mencari pesanan berdasarkan ID
    for (i = 0; i < orderCount; i++){
        if (orders[i].orderID == delorderID){
            found = 1;

            // Menggeser pesanan setelah pesanan yang dihapus
            for (j = i; j < orderCount - 1; j++){
                orders[j] = orders[j + 1];
            }
            orderCount--;  // Mengurangi jumlah pesanan
            printf("Pesanan dengan ID %d berhasil dihapus!\n", delorderID);
            return;
        }
    }
    if (!found){
        printf("Pesanan tidak ditemukan!\n");
    }
}

// Function untuk mengurutkan menu berdasarkan harga
void sortMenuByPrice(){
	int i, j;
    for (i = 0; i < menuCount - 1; i++){
        for (j = 0; j < menuCount - i - 1; j++){
            if (menu[j].price > menu[j + 1].price){
                struct Item temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
    printf("Menu telah diurutkan!\n");
    displayMenu();
}

// Function untuk mengurutkan menu berdasarkan nama
void sortMenuByName(){
	int i,j;
    for (i = 0; i < menuCount - 1; i++){
        for (j = 0; j < menuCount - i - 1; j++){
            if (strcmp(menu[j].name, menu[j + 1].name) > 0){
                struct Item temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
    printf("Menu telah diurutkan!\n");
    displayMenu();
}

// Function untuk menyimpan perubahan yang terjadi pada menu ke file txt
void saveMenu(){
	int i;
    FILE *file = fopen(MENU, "w");
    if (file == NULL){
        printf("Error saat membuka file!\n");
        return;
    }
    // Looping untuk mengirim menu dan datanya ke file txt
    for (i = 0; i < menuCount; i++){
        fprintf(file, "%d,%s,%.2f,%d\n",
                menu[i].id,
                menu[i].name,
                menu[i].price,
                menu[i].stock);
    }
    fclose(file);
}

// Function untuk mengambil menu dan datanya dari file txt
void loadMenu(){
    FILE *file = fopen(MENU, "r");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        return;
    }
    menuCount = 0;
    // Looping untuk mengambil data dari file txt
    while (!feof(file) && menuCount < MAXI){
        struct Item item;
        if (fscanf(file, "%d,%[^,],%f,%d\n",
                   &item.id,
                   item.name,
                   &item.price,
                   &item.stock) == 4) {
            menu[menuCount++] = item;
        }
    }
    fclose(file);
}

// Function untuk menyimpan perubahan yang terjadi pada pesanan ke file txt
void saveOrders(){
	int i;
    FILE *file = fopen(ORDERS, "w");
    if (file == NULL){
        printf("Error saat membuka file!\n");
        return;
    }
    for (i = 0; i < orderCount; i++){
        fprintf(file, "%d,%d,%d,%.2f,%s\n",
                orders[i].orderID,
                orders[i].itemID,
                orders[i].quantity,
                orders[i].totalPrice,
                orders[i].date);
    }
    fclose(file);
}

// Function untuk mengambil menu dan datanya dari file txt
void loadOrders(){
    FILE *file = fopen(ORDERS, "r");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        return;
    }
    orderCount = 0;
    while (!feof(file) && orderCount < MAXO){
        struct Order order;
        if (fscanf(file, "%d,%d,%d,%f,%[^\n]\n",
                   &order.orderID,
                   &order.itemID,
                   &order.quantity,
                   &order.totalPrice,
                   order.date) == 5) {
            orders[orderCount++] = order;
        }
    }
    fclose(file);
}

// Function utama
int main(){
    int choice;
    int isAdmin = 0;  // Sebagai penanda apakah admin atau bukan
    loadMenu();
    loadOrders();
    isAdmin = loginAsAdmin();
    system("cls");
	// Looping selama user belum memilih keluar
    while(1){
        printf("Selamat datang\n");
        if (isAdmin){ // Jika user adalah admin
            printf("1. Menampilkan menu\n");
            printf("2. Menambahkan menu baru\n");
            printf("3. Mengubah menu yang sudah ada\n");
            printf("4. Menghapus menu yang sudah ada\n");
            printf("5. Menampilkan pesanan\n");
            printf("6. Mengedit pesanan\n"); 
    		printf("7. Menghapus pesanan\n"); 
    		printf("8. Keluar\n");
		} 
		else { // Jika user adalah customer
            printf("1. Menampilkan menu\n");
            printf("2. Memesan menu\n");
            printf("3. Mengurutkan menu berdasarkan harga\n");
            printf("4. Mengurutkan menu berdasarkan nama\n");
            printf("5. Keluar\n");
        }
        printf("Masukkan pilihanmu: ");
        scanf("%d", &choice);
        system("cls");
		// Condition untuk setiap pilihan
        switch (choice){
            case 1: // Menampilkan menu
                displayMenu();
                break;
            case 2:
                if (isAdmin){ // Jika user adalah admin, maka menuju function addMenu untuk menambahkan menu baru
                    addMenu();
                } 
				else { // Jika user adalah customer, maka menuju function order untuk memesan menu
                    order();
                }
                break;
            case 3:
                if (isAdmin){ // Jika user adalah admin, maka menuju function editMenu untuk mengubah menu yang sudah ada
                    editMenu();
                } 
				else { // Jika user adalah customer, maka menuju function sortMenuByPrice untuk mengurutkan menu berdasarkan harga 
                    sortMenuByPrice();
                }
                break;
            case 4:
                if (isAdmin){ // Jika user adalah admin, maka menuju function deleteMenu untuk menghapus menu yang sudah ada
                    deleteMenu();
                } 
				else { // Jika user adalah customer, maka menuju function sortMenuByName untuk mengurutkan menu berdasarkan nama menu
                    sortMenuByName();
                }
                break;
            case 5:
                if (isAdmin){ // Jika user adalah admin, maka menuju function displayOrders untuk menampilkan pesanan
                    displayOrders();
                } 
				else { // Jika user adalah customer, maka menuju function saveMenu dan saveOrders untuk menyimpan segala perubahan yang ada ke file txt
                    saveMenu();
                    saveOrders();
                    printf("Thank you for Coming!\n");
                    return 0;
                }
                break;
            case 6: // Mengubah pesanan yang sudah ada
                if (isAdmin){
                    editOrder();
                }
                break;
            case 7: // Mengubah pesanan yang sudah ada
                if (isAdmin){
                    deleteOrder();
                }
                break;
            case 8: // Menyimpan perubahan yang ada pada menu dan pesanan ke dalam file txt
                if (isAdmin){
                    saveMenu();
                    saveOrders();
                    printf("Thank you for Coming!\n");
                    return 0;
                }
                break;
            default: // Jika user memilih selain pilihan yang ada, maka pilihan invalid
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
