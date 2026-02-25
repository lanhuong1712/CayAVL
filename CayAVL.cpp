#include <iostream>
using namespace std;

// ===== CẤU TRÚC NODE =====
struct Node {
    int khoa;
    Node *trai;
    Node *phai;
    int chieuCao;
};

// ===== HÀM TIỆN ÍCH =====
int layChieuCao(Node* n) {
    return (n == NULL) ? 0 : n->chieuCao;
}

int lonHon(int a, int b) {
    return (a > b) ? a : b;
}

Node* taoNode(int khoa) {
    Node* node = new Node();
    node->khoa = khoa;
    node->trai = node->phai = NULL;
    node->chieuCao = 1;
    return node;
}

// ===== XOAY PHẢI =====
Node* xoayPhai(Node* y) {
    Node* x = y->trai;
    Node* T2 = x->phai;

    x->phai = y;
    y->trai = T2;

    y->chieuCao = lonHon(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;
    x->chieuCao = lonHon(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;

    return x;
}

// ===== XOAY TRÁI =====
Node* xoayTrai(Node* x) {
    Node* y = x->phai;
    Node* T2 = y->trai;

    y->trai = x;
    x->phai = T2;

    x->chieuCao = lonHon(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;
    y->chieuCao = lonHon(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;

    return y;
}

int heSoCanBang(Node* n) {
    return (n == NULL) ? 0 : layChieuCao(n->trai) - layChieuCao(n->phai);
}

// ===== THÊM NODE =====
Node* them(Node* root, int khoa) {
    if (root == NULL)
        return taoNode(khoa);

    if (khoa < root->khoa)
        root->trai = them(root->trai, khoa);
    else if (khoa > root->khoa)
        root->phai = them(root->phai, khoa);
    else
        return root;

    root->chieuCao = 1 + lonHon(layChieuCao(root->trai), layChieuCao(root->phai));
    int canBang = heSoCanBang(root);

    if (canBang > 1 && khoa < root->trai->khoa)
        return xoayPhai(root);

    if (canBang < -1 && khoa > root->phai->khoa)
        return xoayTrai(root);

    if (canBang > 1 && khoa > root->trai->khoa) {
        root->trai = xoayTrai(root->trai);
        return xoayPhai(root);
    }

    if (canBang < -1 && khoa < root->phai->khoa) {
        root->phai = xoayPhai(root->phai);
        return xoayTrai(root);
    }

    return root;
}

// ===== TÌM NODE NHỎ NHẤT =====
Node* timNhoNhat(Node* root) {
    while (root->trai != NULL)
        root = root->trai;
    return root;
}

// ===== XÓA NODE =====
Node* xoa(Node* root, int khoa) {
    if (root == NULL)
        return root;

    if (khoa < root->khoa)
        root->trai = xoa(root->trai, khoa);
    else if (khoa > root->khoa)
        root->phai = xoa(root->phai, khoa);
    else {
        if (root->trai == NULL || root->phai == NULL) {
            Node* temp = root->trai ? root->trai : root->phai;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = timNhoNhat(root->phai);
            root->khoa = temp->khoa;
            root->phai = xoa(root->phai, temp->khoa);
        }
    }

    if (root == NULL)
        return root;

    root->chieuCao = 1 + lonHon(layChieuCao(root->trai), layChieuCao(root->phai));
    int canBang = heSoCanBang(root);

    if (canBang > 1 && heSoCanBang(root->trai) >= 0)
        return xoayPhai(root);

    if (canBang > 1 && heSoCanBang(root->trai) < 0) {
        root->trai = xoayTrai(root->trai);
        return xoayPhai(root);
    }

    if (canBang < -1 && heSoCanBang(root->phai) <= 0)
        return xoayTrai(root);

    if (canBang < -1 && heSoCanBang(root->phai) > 0) {
        root->phai = xoayPhai(root->phai);
        return xoayTrai(root);
    }

    return root;
}

// ===== TÌM KIẾM =====
bool tim(Node* root, int khoa) {
    if (root == NULL) return false;
    if (root->khoa == khoa) return true;

    if (khoa < root->khoa)
        return tim(root->trai, khoa);
    else
        return tim(root->phai, khoa);
}

// ===== DUYỆT INORDER =====
void duyetGiua(Node* root) {
    if (root != NULL) {
        duyetGiua(root->trai);
        cout << root->khoa << " ";
        duyetGiua(root->phai);
    }
}

// ===== HÀM MAIN =====
int main() {
    Node* root = NULL;
    int chon, giaTri;

    do {
        cout << "\n1.Them  2.Xoa  3.Tim  4.Duyet  0.Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1:
            cin >> giaTri;
            root = them(root, giaTri);
            break;

        case 2:
            cin >> giaTri;
            root = xoa(root, giaTri);
            break;

        case 3:
            cin >> giaTri;
            if (tim(root, giaTri))
                cout << "Tim thay\n";
            else
                cout << "Khong tim thay\n";
            break;

        case 4:
            duyetGiua(root);
            cout << endl;
            break;
        }

    } while (chon != 0);

    return 0;
}