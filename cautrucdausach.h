
// DANH SACH TUYEN TINH
struct DauSach {
	char ISBN[10];
	char tensach[30];
	int sotrang;
	char tacgia[20];
	int nxb;
	char theloai[15];
	NodeSach* First = NULL;// tro den sach thuoc dau sach tuong ung

	/*
	 * Cac thuoc tinh them
	 */
	int soluotmuon; 	// so luot muon sach
	int soluong;	// so luong sach cua dau sach

	DauSach() {
	}
	DauSach(char* isbn, char* ten, int st, char* tg, int xb, char* tl) {
		strcpy(ISBN, isbn);
		strcpy(tensach, ten);
		sotrang = st;
		strcpy(tacgia, tg);
		nxb = xb;
		strcpy(theloai, tl);
		First = NULL;

		soluong = 0;
		soluotmuon = 0;
	}

};

struct DS_DauSach {
	int n;
	DauSach* nodes[MAX_SIZE_DAUSACH];// danh sach tuyen tinh la mot mang con tro
// ham tao ham huy
	DS_DauSach() {
		n = 0;
	}
	~DS_DauSach() {
		printf("Free memory dau sach + dms \n");
		while (n) {
			DeleteAllNodeSach(nodes[n - 1]->First);// da cap phat thi phai thu hoi moi tiet kiem bo nho
			delete nodes[--n];//thu hoi bo nho
		}
	}
};


int listIndexDauSachSearch[MAX_SIZE_DAUSACH];// mang chua cac dau sach
int sizeListIndexDauSachSearch = 0;//m la size dau sach, dung de ve do hoa page dau sach khi tim

void InsertDauSach(DS_DauSach& DSDS, DauSach* dausach, int position);
void AddDauSach(DS_DauSach& DSDS, DauSach* dausach);
void DeleteDauSach(DS_DauSach& DSDS, char* ISBN);
int ExistsDauSach(DS_DauSach& DSDS, char* ISBN);



/*
 * Them DauSach vao vi tri position trong DSDS
 */
 // dung trong ham ADD
void InsertDauSach(DS_DauSach &DSDS, DauSach *dausach, int position){
	if(position < 0){
		printf("Vi tri them dau sach khong hop le \n");
		return;
	}
	// neu position >= DSDS.n thi se Insert vao cuoi danh sach
	for(int i=DSDS.n; i>position; i--){
		DSDS.nodes[i] = DSDS.nodes[i-1];
	}
	DSDS.nodes[position] = dausach;
	DSDS.n++; 
}


/*
 * Them DauSach khi nguoi dung nhap
 * Ham AddDauSach se tu dong tim vi tri Insert thich hop
 */
//d in cac dau sach trong thu vien theo tung the loai, trung the loai thi in theo ten
void AddDauSach(DS_DauSach& DSDS, DauSach* dausach) {
	if (DSDS.n > MAX_SIZE_DAUSACH)//ok
		printf("DSDS day \n");
	else {
		for (int i = 0; i < DSDS.n; i++) {
			if (strcmp(dausach->theloai, DSDS.nodes[i]->theloai) < 0) {
				InsertDauSach(DSDS, dausach, i);
				return;
			}

			if (strcmp(dausach->theloai, DSDS.nodes[i]->theloai) == 0) {
				if (strcmp(dausach->tensach, DSDS.nodes[i]->tensach) <= 0) {
					InsertDauSach(DSDS, dausach, i);
					return;
				}
			}
		}

		DSDS.nodes[DSDS.n++] = dausach;//
		// nen la cho bat dieu kien cho ham insert k co >=dsds.n vi cuoi cung thi no cung k them xa hon cuoi dc
		//ma minh da them ve cuoi o cho nay roi
	}
}


void InsertLastDauSach(DS_DauSach& DSDS, DauSach* dausach) {
	// su dung khi doc file
	if (DSDS.n > MAX_SIZE_DAUSACH)
		printf("DSDS day \n");
	else {
		DSDS.nodes[DSDS.n++] = dausach;
	}
}


// kiem Isbn// dung de bat dieu kien khi ma nhap cung ma ISBN ton tai roi thi la lang len
int ExistsDauSach(DS_DauSach& DSDS, char* ISBN) {
	for (int i = 0; i < DSDS.n; i++) {
		if (strcmp(DSDS.nodes[i]->ISBN, ISBN) == 0) {
			return i;
		}
	}
	return -1;
}



/*
 * Cap nhat Dau Sach tai vi tri i, noi dung la dausach
 */
 // Hieu chinh ne
void UpdateDauSach(DS_DauSach& DSDS, DauSach* dausach, int i) {
	if (i >= DSDS.n || i < 0) printf("Khong the update dau sach");
	else {
		// Gan dia chi con tro DMS First vao dausach moi
		// kieu la cho dau sach moi tro len du lieu cua dau sach cu
		dausach->First = DSDS.nodes[i]->First;
		dausach->soluong = DSDS.nodes[i]->soluong;
		dausach->soluotmuon = DSDS.nodes[i]->soluotmuon;

		delete DSDS.nodes[i];//giai phong tren tung vung nho, diem hay nhat cua mang con tro
		//thao tac xoa
		//mang con tro phai lien tuc nen la phai co no lai, con tro tro den o nho nao thi ke no
		for (int j = i; j < DSDS.n; j++) {
			DSDS.nodes[j] = DSDS.nodes[j + 1];
		}
		DSDS.n--;
		AddDauSach(DSDS, dausach);
	}
}

 
 // cac thao tac de xoa 1 dau sach, DAU SACH CO sach thi khong cho xoa
 int Kiemtraxoadausach(DS_DauSach &DSDS, char tendausach[30]){
	for(int i=0;i<DSDS.n;i++){
		if(strcmp(DSDS.nodes[i]->tensach,tendausach)==0) return i;//bang vi tri cho do
	}
	return -1;
}

  //Xoa Dau Sach theo ten dausach
 
 void DeleteDauSach(DS_DauSach &DSDS, char tendausach[30]){
 	// Tim vi tri Dau sach muon xoa
 	int i = Kiemtraxoadausach(DSDS,tendausach);//    
 	if(i == -1){
 		printf("\nKhong the xoa");
 	}else{
 		
 		for(;i<DSDS.n-1; i++){
 			DSDS.nodes[i]= DSDS.nodes[i+1];// thuat toan xoa 
 			
 		}
 		DSDS.n--;
 	}
 }
 
// Ham nay dung de kiem tra 2 chuoi

// kiem tra chuoi str1 co la chuoi con cua str2 hay k
bool IsPrefix( char* pre, char* str) {
	
	if (strlen(pre) > strlen(str)) return false;
	for (int i = 0; i < strlen(pre); i++) {
		if (pre[i] != str[i]) return false;
	}
	return true;
}

/*
 * Loc danh sach cac Dau Sach co ten bat dau la: strFind
 * Luu vi tri cua cac Dau Sach vao 1 mang: listIndexDauSachSearch[]
 * Size cua list se duoc luu vao bien: m
 */
 //lay dau sach o muc tim dau sach
void GetListNodes(DS_DauSach& DSDS,  char* strFind, int& m) {
	m = 0;
	for (int i = 0; i < DSDS.n; i++) {
		if (IsPrefix(strFind, DSDS.nodes[i]->tensach)==true) {
			listIndexDauSachSearch[m++] = i;
		//	cout<<"\ni ne: ";
		//	cout<<i;
		}
	//	cout<<"\nVong lap thu nhat: "<<i;
	//	cout<<"\n m ne : "<<m;
	}
}
// m la so luong phan tu cua mang, de nua lam do hoa can lay toi bien m


// muon tra xai
int GetSepPosition(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++) {
		//cout<<"______________s["<<i<"] = "<<s[i];
		cout<<"______________ "<<s[i];

		if (s[i] == '-') return i;
	}
	return -1;
}

/*
 * Tim DauSach theo masach 
 * Tra ve node cua DauSach can tim
 */
 
 // muon tra LAM MAT DA CHO MUON DA THANH LY
DauSach* GetDauSach(DS_DauSach& DSDS, char* masach) { //BHK-1
	NodeSach* node; 
	int sepPos = GetSepPosition(masach);// tra ve vi tri    BHK-1  //sepos =3
	cout<<"\n_____________ sepPos = "<<sepPos;
	char isbn[sepPos + 1]; 
	int indexSach = 0;
	for (int i = 0; i < sepPos; i++){
		cout<<"\n================ : "<<masach[i];
		isbn[i] = masach[i];
	}
	isbn[sepPos] = '\0';
	for (int i = sepPos + 1; i < strlen(masach); i++) {
		cout<<"\n_____________ i = "<<i;
		indexSach = indexSach * 10 + (masach[i] - '0');
		cout<<"\n_______________ index = "<<indexSach;
	}

	for (int i = 0; i < DSDS.n; i++) {
		if (strcmp(DSDS.nodes[i]->ISBN, isbn) == 0) {
			cout<<"\n____________indexSach = "<<indexSach;
			cout<<"\n____________DSDS.nodes[i]->soluong = "<<DSDS.nodes[i]->soluong;
			if (indexSach < DSDS.nodes[i]->soluong) return DSDS.nodes[i];
			else break;
		}

	}
	return NULL;
}

/*
 * Tim DauSach theo masach
 * Tra ve index cua DauSach can tim
 */
//int GetIndexDauSach(DS_DauSach& DSDS, char* masach) {
//	int sepPos = GetSepPosition(masach);
//	char isbn[sepPos + 1];
//	for (int i = 0; i < sepPos; i++) isbn[i] = masach[i];
//	isbn[sepPos] = '\0';
//
//	for (int i = 0; i < DSDS.n; i++) {
//		if (strcmp(DSDS.nodes[i]->ISBN, isbn) == 0) {
//			return i;
//		}
//	}
//	return -1;
//}

/*
 * Struct thong ke so luot muon sach cua moi Dau Sach
 */
struct LuotMuonSach {
	int indexDS;	// vi tri cua DauSach
	int cnt;		// so luot muon
};

struct TopSach {
	int n;
	LuotMuonSach* list;// danh sach tuyen tinh la mang  dong
// ham tao

	TopSach(DS_DauSach& DSDS) {
		n = DSDS.n;
		cout<<"\n______________ n = "<<n;
		list = new LuotMuonSach[n];// cap phat cho cac phan tu
		for (int i = 0; i < n; i++) {
			list[i].indexDS = i;
			list[i].cnt = DSDS.nodes[i]->soluotmuon;
		}
		sort();
	}
	~TopSach() {
		delete[] list;// cap phat roi phai thu hoi k thi con ton bo nho hon nua
	}
	// Phan doan
	void partition(int low, int high) {
		int i = low, j = high;
		LuotMuonSach tmp;
		int pivot = list[(low + high) / 2].cnt;
		do {
			while (list[i].cnt > pivot) i++;
			while (list[j].cnt < pivot) j--;
			if (i <= j) {
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
				i++; j--;
			}
		} while (i <= j);

		if (low < j) partition(low, j);
		if (i < high) partition(i, high);
	}
	void sort() {
		// Sap xep theo thu tu cnt giam dan
		// Su dung QuickSort
		partition(0, n - 1);
	}
};



