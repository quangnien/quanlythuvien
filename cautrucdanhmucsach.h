//cau truc danh muc sach la lien ket don
struct Sach {
	char MASACH[15];
	int trangthai;
	/*
	 * 0: Cho muon duoc
	 * 1: Da cho muon
	 * 2: Da thanh ly
	 */
	char vitri[20];

	Sach() {
	}
	Sach(char ms[15], int tt, char vt[20]) {
		strcpy(MASACH, ms);
		trangthai = tt;
		strcpy(vitri, vt);
	}
};

// NODE Sach - DSLK don
struct NodeSach {
	Sach sach;
	NodeSach* next;//noi
};


void InsertFirst_NodeSach(NodeSach*& First, Sach &sach);//first thay doi thamchieu cho no
void InsertAfter_NodeSach(NodeSach*& node, Sach &sach);//tham chieu de toi uu cac hinh thuc chay ct
void InsertLast_NodeSach(NodeSach*& First, Sach &sach);

/*
 * Cap phat bo nho cho Node moi
 */
NodeSach* CreateNodeSach(Sach &sach) {
	NodeSach* node = new NodeSach;
	node->sach = sach;
	return node;
}

void InsertFirst_NodeSach(NodeSach*& First, Sach &sach) {
	NodeSach* newNode = CreateNodeSach(sach);

	newNode->next = First;
	First = newNode;
}


void InsertAfter_NodeSach(NodeSach*& node, Sach &sach) {//node la node trong dslk
	NodeSach* newNode = CreateNodeSach(sach);

	newNode->next = node->next;
	node->next = newNode;
}
// dung trong doc ghi file, va Them sach
void InsertLast_NodeSach(NodeSach*& First, Sach &sach) {
	if (First == NULL) InsertFirst_NodeSach(First, sach);//k cos 
	else {//co it nhat 1 quyen r
		NodeSach* last;
		
		for (last = First; last->next != NULL; last = last->next);
		//chay het vong for ta tim duoc node last
			
		InsertAfter_NodeSach(last, sach);
		//them vao cuoi
	//	cout<<"\nGia tri cua sach them la: "<<last->sach.MASACH;
		
		
	}
}



/*
 * Lay NodeSach tai vi tri position
 */
 // dung cho do hoa, de phan trang lay node sach theo vi tri
NodeSach* GetNodeSach(NodeSach* First, int position) {
	NodeSach* node = First;// tao 1 node dau tien
	for (int i = 0; node != NULL; node = node->next) {
		//cout<<"\ni truoc khi tang la: "<<i;
		if (i == position) break;
		++i;
//		cout<<"\ngia tri cua i la"<<i;
//		cout<<"\ngia tri cua position la: "<<position;
	}
	return node;//tra  ve node co vi tri position
}

/*
 * Lay NodeSach theo masach dung cho do hoa cua muon tra
 */
 // dung cho muon tra
NodeSach* GetNodeSach(NodeSach* First, char* masach) {
	for (NodeSach* node = First; node != NULL; node = node->next) {
		if (strcmp(node->sach.MASACH, masach) == 0) return node;
	}
	return NULL;
}


//  dung cho update hieu chinh,dung cho muon tra 
//dung cho hieu chinh sach, update lai noi dung sach sau khi da hieu chinh
void UpdateNodeSach(NodeSach*& node, Sach& sach) {//node la node can de hieu chinh
	if (node == NULL) printf("K the update");
	else {
		node->sach=sach;
	}
}
// dung cho muon tra
Sach* GetSach(NodeSach* First, char* masach) {
	for (NodeSach* node = First; node != NULL; node = node->next) {
		if (strcmp(node->sach.MASACH, masach) == 0) return &node->sach;
	}
	return NULL;
}
//void DelFirst(NodeSach *&First) {
//	if (First->next==NULL) {
//		delete First;
//		First= NULL;
//	}
//	//neu danh sach rong
//	if (First== NULL) {
//		return;
//	}
//	NodeSach* p = First;
//	First = First->next;
//	delete p;
//}
//
//void DeleteSachLast(NodeSach *&First) {
//	if (First == NULL) {
//		return;
//	}
//	if (First->next==NULL) {
//		DelFirst(First);
//		
//	}
//	else {
//
//		NodeSach * p = First;
//		while (p->next->next!=NULL) {
//			p = p->next;
//		}
//		p->next = p->next->next;
//	}
//	
//}
// giai phong vung nho
void DeleteAllNodeSach(NodeSach*& First) {
	NodeSach* removeNode;
	while (First != NULL) {
		removeNode = First;
		First = First->next;
		delete removeNode;
	}
}





