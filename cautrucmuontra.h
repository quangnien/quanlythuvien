struct MuonTra {
	char MASACH[15];
	char ngaymuon[10];
	char ngaytra[10]; 
	int trangthai;
	/*
	 * 0: Dang muon
	 * 1: Da tra
	 * 2: Lam mat
	 */
	MuonTra() {
	}
	MuonTra(char* ms, char* muon, char* tra, int tt) {
		strcpy(MASACH, ms);
		strcpy(ngaymuon, muon);
		strcpy(ngaytra, tra);
		trangthai = tt;
	}
};

struct NodeMuonTra {
	MuonTra muontra;
	NodeMuonTra* next;
};

struct DS_MuonTra {
	NodeMuonTra* First = NULL;

	/*
	* thuoc tinh them
	*/
	int total;	// tong so luong sach da muon
	int chuaTra;	// so luong sach dang muon + lam mat

	DS_MuonTra() {
		First = NULL;
		total = 0;
		chuaTra = 0;
	}
	
	~DS_MuonTra() {
	}
};

NodeMuonTra* CreateNewNode_MuonTra(MuonTra& mt) {
	NodeMuonTra* newNode = new NodeMuonTra;

	newNode->muontra = mt;
	newNode->next = NULL;

	return newNode;
}

void InsertFirst(NodeMuonTra*& First, MuonTra& mt) {
	NodeMuonTra* newNode = CreateNewNode_MuonTra(mt);
	newNode->next = First;
	First = newNode;
}

void InsertFirst_MuonTra(DS_MuonTra& DSMT, MuonTra& mt) {
	InsertFirst(DSMT.First, mt);
}

void InsertAfter(NodeMuonTra*& node, MuonTra& mt) {
	NodeMuonTra* newNode = CreateNewNode_MuonTra(mt);
	newNode->next = node->next;
	node->next = newNode;
}

void InsertAfter_MuonTra(DS_MuonTra& DSMT, MuonTra& mt) {
	InsertAfter(DSMT.First, mt);
}

void InsertLast(NodeMuonTra*& First, MuonTra& mt) {
	if (First == NULL) InsertFirst(First, mt);
	else {
		NodeMuonTra* last;
		for (last = First; last->next != NULL; last = last->next);
		InsertAfter(last, mt);
	}
}

void InsertLast_MuonTra(DS_MuonTra& DSMT, MuonTra& mt) {
	InsertLast(DSMT.First, mt);
	DSMT.total++;
	if (mt.trangthai != 1) DSMT.chuaTra++;
}

// Tra sach + lam mat sach
void Update_MuonTra(DS_MuonTra& DSMT, MuonTra& mt) {
	for (NodeMuonTra* node = DSMT.First; node != NULL; node = node->next) {
		if (strcmp(node->muontra.MASACH, mt.MASACH) == 0 && strlen(node->muontra.ngaytra) == 0) {
			node->muontra = mt;
			if (mt.trangthai == 1) DSMT.chuaTra--;
			return;
		}
	}
}

//void ClearList_MuonTra(DS_MuonTra& DSMT) {
//	NodeMuonTra* removeNode;
//	while (DSMT.First != NULL) {
//		removeNode = DSMT.First;
//		DSMT.First = removeNode->next;
//		delete removeNode;
//	}
//}

void DeleteAllMuonTra(DS_MuonTra& DSMT) {
	NodeMuonTra* removeNode;
	while (DSMT.First != NULL) {
		removeNode = DSMT.First;
		DSMT.First = DSMT.First->next;
		delete removeNode;
	}
}


