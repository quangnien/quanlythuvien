struct DocGia{
	int MATHE;
	char ho[40];
	char ten[20];
	int phai;
		/* 
		 * 0: Nam
		 * 1: Nu
		 */
	int trangthai; 
		/*
		 * 0: Khoa
		 * 1: Hoat dong
		 */
	// dslk don cac sach ma doc gia da va dang muon
	DS_MuonTra mt;
	
	DocGia(){
	}
	DocGia(int mt, char h[40], char t[20], int p, int tt){
		MATHE = mt;
		strcpy(ho, h);
		strcpy(ten, t);
		phai = p;
		trangthai = tt;
	}
};

struct NodeDocGia{
	// key = docgia.MATHE;
	DocGia docgia;
	NodeDocGia *left = NULL;
	NodeDocGia *right = NULL;
};

/*
 * Mang con tro dung de luu danh sach doc gia tu BST
 */
enum ModeDocGia{MODE_MA_THE, MODE_TEN, MODE_QUA_HAN};
struct DS_DocGia{
	int n;
	DocGia *nodes[MAX_DOC_GIA];
	int soNgayQH[MAX_DOC_GIA];
	ModeDocGia mode;
	
	DS_DocGia(){
		mode = MODE_MA_THE;
	}
	~DS_DocGia(){
		
	}
	
	// Duyet InOrder
	void LNR(NodeDocGia* &node){
		if(node == NULL) return;
		LNR(node->left);
		nodes[n++] = &node->docgia;
		LNR(node->right);
	}
	
	void GetAllDocGia(NodeDocGia* &TreeDG){
		Reset();
		LNR(TreeDG);
		// Duyet InOrder thi cac key = MATHE se duoc lay theo thu tu tang dan
		mode = MODE_MA_THE;
	}
	
	int compareDG(DocGia *a, DocGia *b){
		if(mode == MODE_MA_THE){
			return a->MATHE - b->MATHE;
		}else if(mode == MODE_TEN){
			if(strcmp(a->ten, b->ten) == 0){
				return strcmp(a->ho, b->ho);
			}else{
				return strcmp(a->ten, b->ten);
			}
		}
		return 0;
	}
	
	//use quicksort
	void Partition(int low, int high){
		int i = low, j = high;
		DocGia* pivot = nodes[(low+high)/2];
		int qhPivot = soNgayQH[(low+high)/2];
		DocGia* temp;
		int qhTemp;
		
		do{
			if(mode == MODE_QUA_HAN){ 					//Descending
				while(soNgayQH[i] > qhPivot) i++;
				while(soNgayQH[j] < qhPivot) j--;
			}else{ 										//if(mode == MODE_MA_THE || mode == MODE_TEN) => ascending
				while(compareDG(nodes[i], pivot) < 0) i++;
				while(compareDG(nodes[j], pivot) > 0) j--;
			}
			if(i <= j){
				temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
				if(mode == MODE_QUA_HAN){
					qhTemp = soNgayQH[i];
					soNgayQH[i] = soNgayQH[j];
					soNgayQH[j] = qhTemp;
				}
				i++; j--;
			}
		}while(i <= j);
		
		if(low < j) Partition(low, j);
		if(i < high) Partition(i, high);
	}
	
	void SortMaTheDocGia(){
		if(mode != MODE_MA_THE && n > 0){
			mode = MODE_MA_THE;	
			Partition(0, n-1);  
		}
	}
	
	void SortTenDocGia(){
		if(mode != MODE_TEN && n > 0){
			mode = MODE_TEN;
			Partition(0, n-1);
		}
	}
	
	void SortDocGiaQuaHan(){
		if(mode != MODE_QUA_HAN && n > 0){
			mode = MODE_QUA_HAN;
			Partition(0, n-1);
		}
	}
	
	void GetDocGiaQuaHan(NodeDocGia* &TreeDG){
		Reset();	ResetQH();
		Queue<NodeDocGia*> q;
		if(TreeDG != NULL) q.push(TreeDG);
		NodeDocGia* nodeDG;
		bool hasDGQH;
		int i;
		
		while(!q.empty()){
			nodeDG = q.front();	
			q.pop();
			
			i = 0;
			soNgayQH[n] = 7;
			hasDGQH = false;
			
			if(nodeDG->docgia.mt.chuaTra > 0 && nodeDG->docgia.mt.First != NULL){
				// Neu thu tu muon tra duoc luu theo thu tu thoi gian tang dan, thi ta chi can lay duoc 1 node la dung..
				for(NodeMuonTra *nodeMT = nodeDG->docgia.mt.First; nodeMT != NULL; nodeMT = nodeMT->next){
					if(strlen(nodeMT->muontra.ngaytra) == 0){
						// chua tra sach
						if(DiffTime(GetSystemDate(), nodeMT->muontra.ngaymuon) > soNgayQH[n]*24*60*60){
							soNgayQH[n] = DiffTime(GetSystemDate(), nodeMT->muontra.ngaymuon) / (24*60*60);
							hasDGQH = true;
						}
					
						if(++i >= nodeDG->docgia.mt.chuaTra) break;
					}
				}
			}
			
			if(hasDGQH) nodes[n++] = &nodeDG->docgia;
			
			if(nodeDG->left != NULL) q.push(nodeDG->left);
			if(nodeDG->right != NULL) q.push(nodeDG->right);
		}
		SortDocGiaQuaHan();
	}

	void Reset(){
		n = 0;
	}
	
	void ResetQH(){
		for(int i=0; i<MAX_DOC_GIA; i++) soNgayQH[i] = 0;
	}
};

void InsertDocGia(NodeDocGia* &node, DocGia &dg){
	if(node == NULL){
		node = new NodeDocGia;
		node->docgia = dg;
		node->left = NULL;
		node->right = NULL;
	}else{
		if(dg.MATHE < node->docgia.MATHE){
			InsertDocGia(node->left, dg);
		}else if(dg.MATHE > node->docgia.MATHE){
			InsertDocGia(node->right, dg);
		}
	}
}

NodeDocGia* SearchDocGia(NodeDocGia* &treeDG, int maDocGia){
	NodeDocGia* node = treeDG;
	while(node != NULL && node->docgia.MATHE != maDocGia){
		if(maDocGia < node->docgia.MATHE) node = node->left;
		else node = node->right;
	}
	return node;
}

//tim node trai nhat cua cay con phai 
void RemoveDocGia_SpecialCase(NodeDocGia* &node, NodeDocGia* &removeNode){ //node : node the mang , removeNode : node can xoa
	if(node->left != NULL) RemoveDocGia_SpecialCase(node->left, removeNode);
	else{
		removeNode->docgia = node->docgia;
		removeNode = node;
		node = node->right;
	}
}

void RemoveDocGia(NodeDocGia* &node, int maDocGia){
	if(node == NULL) {
		printf("K the xoa doc gia \n");
		return;
	}
	if(maDocGia < node->docgia.MATHE) RemoveDocGia(node->left, maDocGia);
	else if(maDocGia > node->docgia.MATHE) RemoveDocGia(node->right, maDocGia);
	else{
		NodeDocGia *removeNode = node;
		if(node->right == NULL){
			node = node->left;
		}else if(node->left == NULL){
			node = node->right;
		}else{
			RemoveDocGia_SpecialCase(node->right, removeNode);
		}
		
		// Neu chi xoa doc gia chua tung muon sach, thi cau lenh nay khong can thiet
		DeleteAllMuonTra(removeNode->docgia.mt);
		
		delete removeNode;
	}
}

void UpdateDocGia(NodeDocGia* &TreeDG, DocGia &docgia){
	NodeDocGia* nodeUpdate = SearchDocGia(TreeDG, docgia.MATHE);
	if(nodeUpdate == NULL){
		printf("K the update doc gia \n");
	}else{
		docgia.mt = nodeUpdate->docgia.mt; //update DocGia, not update MuonTra, so copy muontra from DocGiaOld to DocGiaNew
		nodeUpdate->docgia = docgia; 	   //update DocGia
	}
}

// Giai phong bo nho
void DeleteMemoryDocGia(NodeDocGia* &node){
	if(node != NULL){
		DeleteMemoryDocGia(node->left);
		DeleteMemoryDocGia(node->right);
		
		DeleteAllMuonTra(node->docgia.mt); //delete MuonTra before delete DocGia
		
		delete node;
//		node = NULL;
	}
}



// Random Ma doc gia : LKD, quan li bang 2 con tro
struct Node_ID{
	int id; 
	Node_ID *next;
};

struct List_ID{
	Node_ID *head;
	Node_ID *tail;
	
	List_ID(){
		head = NULL;
		tail = NULL;
	}
	~List_ID(){
		Node_ID *removeNode;
		while(head != NULL){
			removeNode = head;
			head = head->next;
			delete removeNode;
		}
		tail = head;
	}
};

// khai bao instance cua List_ID
List_ID listID;


Node_ID* createNode_ID(int id){
	Node_ID *node = new Node_ID;
	node->id = id;
	node->next = NULL;
	return node;
}

void insertHead_ID(int id){
	Node_ID *newNode = createNode_ID(id);
	
	if(listID.head == NULL){
		listID.head = newNode;
		listID.tail = newNode;
	}else{
		newNode->next = listID.head;
		listID.head = newNode;
	}
}

void insertTail_ID(int id){
	if(listID.tail == NULL){
		insertHead_ID(id);
	}else{
		Node_ID *newNode = createNode_ID(id);
		listID.tail->next = newNode;
		listID.tail = newNode;
	}
}

void insertAfter_ID(Node_ID *nodeBefore, int id){
	if(nodeBefore == NULL) return;
	Node_ID *newNode = createNode_ID(id);
	newNode->next = nodeBefore->next;
	nodeBefore->next = newNode;
}

void deleteAfter_ID(Node_ID *nodeBefore){
	if(nodeBefore == NULL || nodeBefore->next == NULL) return;
	Node_ID *removeNode = nodeBefore->next;
	nodeBefore->next = removeNode->next;
	delete removeNode;
}

void delete_ID(int id){
	if(listID.head != NULL && listID.head->id == id){
		Node_ID *removeNode = listID.head;
		listID.head = removeNode->next;
		//delete listID.head;
		delete removeNode;
		return;
	}
	
	for(Node_ID *node = listID.head; node->next != NULL; node = node->next){
		if(node->next->id == id){
			deleteAfter_ID(node);
		}
	}
}

// LNR
void Duyet_DG_ID(NodeDocGia* &nodeDG){
	if(nodeDG == NULL) return;
	Duyet_DG_ID(nodeDG->left);
	insertTail_ID(nodeDG->docgia.MATHE);
	Duyet_DG_ID(nodeDG->right);
}

void AddRangeListID(){
	insertHead_ID(START_ID_DG);
	insertTail_ID(END_ID_DG);
}

Node_ID* Node_ID_Random(){
	int maxDistance = 1; //khoang cach max 
	Node_ID *nodeStart = NULL;
	
	int counttg=0;
	for(Node_ID *node = listID.head; node->next != NULL; node = node->next){
		if(node->next->id - node->id > maxDistance){
			maxDistance = node->next->id - node->id;
			nodeStart = node;
		}else if(node->next->id - node->id == maxDistance && rand()%2){ //0:false, 1:true
			maxDistance = node->next->id - node->id;
			nodeStart = node;
		}
	}
	counttg =0;
		
	if(maxDistance == 1){
		printf("Full Array\n");
	}
	return nodeStart;
}





