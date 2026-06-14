#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//建立結構體tree，幫struct tree取別名"node"
struct tree
{
	int data;
	struct tree* right, * left;
};
typedef struct tree node;

//(回傳根節點)建立二元樹(根節點，一維數列，陣列大小)
node* create(node* root, int arr[], int size);

//()中序走訪(根節點) ==> 該函數打印結果為由小到大/左根右
void inorder(node* root);

//()前序走訪(根節點) ==> 複製二元樹，類似資料夾結構/根左右
void preorder(node* root);

//()後序走訪(根節點) ==> 刪除樹，釋放記憶體，運算式求值，統計子樹資訊 /左右根
void postorder(node* root);

//(回傳搜尋節點的地址)搜尋節點(根節點，欲搜尋的數值)
node* search(node* root, int val);

//(回傳最小值節點)找最小值(根節點)
node* find_min(node* root);

//(回傳最大值節點)找最小值(根節點)
node* find_max(node* root);

//(回傳節點數量)計算節點數量(根節點)
int cnt(node* root);

//(回傳樹高)樹高計算(根節點)
int height(node* root);

//(葉節點數)計算葉節點數(根節點)
int leafcnt(node* root);

//(回傳根節點)刪除節點(根節點，欲刪除的數值)
node* delete_node(node* root, int val);

int main()
{
	int arr[] = { 3,5,7,9,1,8,4,2,6 };
	int size = sizeof(arr) / sizeof(arr[0]);

	node* root = NULL;
	root = create(root, arr, size);

	preorder(root);
	printf("\n");
	find_min(root);
	printf("%d\n", height(root));

	return 0;
}

node* create(node* root, int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		//creating a new node :: declare -> debug -> initialize
		node* newnode = (node*)malloc(sizeof(node));
		if (newnode == NULL)
		{
			printf("create::malloc fail\n");
			return root;
		}
		newnode->data = arr[i];
		newnode->right = NULL;
		newnode->left = NULL;

		//root node verification.
		if (root == NULL)
		{
			root = newnode;
		}

		//non-root node.
		else
		{
			//current pointer is used to locate the position for new leaf node.
			node* current = root;
			//parent pointer is used to track the parent node of current. 
			node* parent = NULL;

			//current searching
			while (current != NULL)
			{
				parent = current;
				if (arr[i] > current->data)
					current = current->right;
				else
					current = current->left;
			}
			//connecting the newnode.
			if (arr[i] > parent->data)
			{
				parent->right = newnode;
			}
			else
				parent->left = newnode;
		}
	}
	return root;
}

void inorder(node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void preorder(node* root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(node* root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

node* search(node* root, int val)
{
	node* current = root;
	while (current != NULL)
	{
		if (val == current->data)
		{
			//printf("%d is in the BST.\n", val);
			return current;
		}
		else
		{
			if (val > current->data)
				current = current->right;
			else
				current = current->left;
		}
	}
	//printf("%d is not in the BST.\n", val);
	return NULL;
}

node* find_min(node* root)
{
	if (root == NULL)
	{
		printf("find_min::root is NULL\n");
		return NULL;
	}

	node* current = root;
	while (current->left != NULL)
		current = current->left;


	return current;
}

node* find_max(node* root)
{
	if (root == NULL)
	{
		printf("find_max::root is NULL\n");
		return NULL;
	}

	node* current = root;
	while (current->right != NULL)
		current = current->right;

	return current;
}

int cnt(node* root)
{
	if (root == NULL)
		return 0;

	return 1 + cnt(root->right) + cnt(root->left);
}

int height(node* root)
{
	if (root == NULL)
		return 0;

	int right = height(root->right);
	int left = height(root->left);

	if (left > right)
		return left + 1;
	else
		return right + 1;
}

int leafcnt(node* root)
{
	if (root == NULL)
		return 0;

	if (root->right == NULL && root->left == NULL)
		return 1;

	return leafcnt(root->right) + leafcnt(root->left);
}

node* delete_node(node* root, int key)
{
	if (root == NULL)
		return NULL;

	// 1. 往左子樹找
	if (key < root->data)
	{
		root->left = delete_node(root->left, key);
	}

	// 2. 往右子樹找
	else if (key > root->data)
	{
		root->right = delete_node(root->right, key);
	}

	// 3. 找到要刪的節點
	else
	{
		// 情況1：葉節點
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}

		// 情況2：只有一個子節點（右）
		else if (root->left == NULL)
		{
			node* temp = root->right;
			free(root);
			return temp;
		}

		// 情況2：只有一個子節點（左）
		else if (root->right == NULL)
		{
			node* temp = root->left;
			free(root);
			return temp;
		}

		// 情況3：兩個子節點
		else
		{
			node* temp = find_min(root->right);

			root->data = temp->data;

			root->right = delete_node(root->right, temp->data);
		}
	}

	return root;
}