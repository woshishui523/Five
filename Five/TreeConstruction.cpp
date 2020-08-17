/*
* 文件名称：TreeConstruction.cpp
* 摘    要：树基础操作的实现文件
*
* 当前版本：版本3.0
* 修改内容：增加广度优先遍历函数			BFSTraverse
*			增加基于BFS的目标搜索函数		SearchDataByBFS
*			增加目标结点的分值修改函数	    ModifyNodeScore
*			修改树的创建函数为添加孩子函数  BuildNodeChildren
* 历史版本：版本2.0
* 修改内容：完善注释、修改变量名称、增加孩子结点计数变量
* 历史版本：版本1.0
*
* 作    者：LiuRuiGuang && WuYue
* 完成时间：2020年8月8日
*/


#include <iostream>
using namespace std;
#include <queue>	//使用STL中的队列
#include "TreeConstruction.h"

/*
* 函数名称：CreateListNode
* 描    述：创建链表结点
* 函数输入：PNODE pChild待插入的树孩子结点的指针
* 函数输出：PLISTNODE pNewListNode链表结点的指针
* 调用函数：无
*/
PLISTNODE CreateListNode(PNODE pChild)
{
	PLISTNODE pNewListNode = new LISTNODE;	//新建一个链表的结点
	if (NULL == pNewListNode)
	{
		cout << "分配失败，程序终止！" << endl;
		exit(-1);	//异常退出
	}
	//分配成功
	pNewListNode->m_pNodeAddress = pChild;	//将树的孩子指针赋值给链表结点的数据域
	pNewListNode->m_pNext = NULL;	//链表结点的指针必须初始化

	return pNewListNode;	//返回新建结点的地址
}

/*
* 函数名称：CreateList
* 描    述：使用动态分配的方法创建一个空链表
* 函数输入：无
* 函数输出：PLISTNODE pHeadListNode，返回动态链表的头结点的地址
* 调用函数：无
*/
PLISTNODE CreateList(void)
{
	PLISTNODE pHeadListNode = new LISTNODE;	//创建一个头结点
	if (NULL == pHeadListNode)//判断头节点是否分配成功
	{
		cout << "分配失败，程序终止！" << endl;
		exit(-1);	//异常退出
	}
	else
	{
		pHeadListNode->m_pNodeAddress = NULL;
		pHeadListNode->m_pNext = NULL;	
		return pHeadListNode;	//分配成功，返回头结点
	}
}


/*
* 函数名称：InsertListNodeByTail
* 描    述：尾插法,在链表中插入链表的结点
* 函数输入：PLISTNODE pListTail链表的尾指针, PLISTNODE pListNew带插入的新链表结点
* 函数输出：pListTail返回当前链表的尾指针
* 调用函数：无
*/
PLISTNODE InsertListNodeByTail(PLISTNODE pListTail, PLISTNODE pListNew)
{
	pListTail->m_pNext = pListNew;	//将新生成的链表结点挂到原链表上
	pListNew->m_pNext = NULL;	//尾结点的指针域始终为空
	pListTail = pListNew;	//尾指针始终指向尾结点

	return pListTail;
}

/*
* 函数名称：DeleteListNode
* 描    述：仅负责删除链表的结点
* 函数输入：PLISTNODE pListFront要删除的链表目标结点的前一个结点
* 函数输出：无
* 调用函数：无
*/
void DeleteListNode(PLISTNODE pListFront)
{
	PLISTNODE pListTem = pListFront->m_pNext;	//要删除的链表的目标结点

	//删除目标链表结点
	//“当前链表结点”前一个结点的指针，指向“当前链表结点”的下一个结点，跨过当前结点
	pListFront->m_pNext = pListTem->m_pNext;

	delete pListTem;	//释放当前链表结点的空间
	pListTem = NULL;

	return;
}



/*
* 函数名称：CreateNode
* 描    述：创建树的结点，并通过形参接收的参数初始化树结点的成员变量
* 函数输入：int data棋谱编码, int score评估的分值
* 函数输出：PNODE pNew新建的树结点指针
* 调用函数：CreateList创建空链表
*/
PNODE CreateNode(int data, int score)
{
	PNODE pNew = new NODE;	//在堆中创建一个结点

	if (NULL == pNew)	//如果空间分配失败
	{
		cout << "score输入错误，请重新输入！" << endl;
		exit(-1);	//异常退出
	}
	else  //结点创建成功
	{
		pNew->m_data = data;	//存储棋子的位置
		pNew->m_score = score;//存储分数
		pNew->m_ChildNum = 0;	//初始化孩子结点的个数
		//树结点的父结点指针
		pNew->m_pParent = NULL;	//避免野指针

		//创建一个孩子指针的链表
		pNew->m_pChildList = CreateList();	//先创建一个空链表
		pNew->m_pListTail = pNew->m_pChildList;	//空链表的尾结点就是头结点
	}

	return pNew;	//返回新建结点的地址
}

/*
* 函数名称：SearchNodeByData
* 描    述：根据每一时刻棋盘的编码，来搜索树的目标结点，并返回结点指针
			搜索方式是深度优先
* 函数输入：PNODE pTemNode搜索的起始结点, int goalData目标结点的分数
* 函数输出：PNODE temp目标树结点的指针
* 调用函数：SearchNodeByData递归调用
*/
PNODE SearchNodeByData(PNODE pTreeRoot, int goalData)
{
	//从根结点开始访问
	PNODE pTem = pTreeRoot;	//初始化当前结点
	PNODE temp = NULL;
	//如果当前结点是目标结点
	if ((NULL != pTem) && (goalData == pTem->m_data))
	{
		temp = pTem;
	}
	else //当前结点不是目标结点
	{
		//在当前结点不是目标结点，则搜索他的孩子
		PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//指向链表的首结点
		//横向遍历链表的所有孩子结点
		//如果当前链表结点非空，表示有孩子结点，则进入循环
		while (NULL != pTemListNode)
		{
			PNODE pTemNode = pTemListNode->m_pNodeAddress;	//当前链表结点所指向的孩子结点
			//对该孩子结点进行递归搜索
			temp = SearchNodeByData(pTemNode, goalData);
			//如果搜索到目标结点，则结束循环递归
			if (NULL != temp)
			{
				break;	//结束循环
			}
			pTemListNode = pTemListNode->m_pNext;	//指向链表的下一个结点
		}

	}

	return temp;	//返回目标结点的指针
}


/*
* 函数名称：InsertNode
* 描    述：插入一棵树结点
* 函数输入：PNODE pTem被插入的树结点, PNODE pNew待插入新的树结点
* 函数输出：无
* 调用函数：无
*/
void InsertNode(PNODE pTem, PNODE pNew) 
{
	PLISTNODE pListTail = pTem->m_pListTail;	//当前结点的孩子结点链表的尾指针

	PLISTNODE pListNew = CreateListNode(pNew);	//通过新的树结点创建一个链表结点
	//将新建结点通过尾插法，插入当前的结点中
	pTem->m_pListTail = InsertListNodeByTail(pListTail, pListNew);	//将孩子结点的指针插入链表中

	pNew->m_pParent = pTem;	//更新父结点指针
	(pTem->m_ChildNum)++;	//更新被插入结点的孩子结点的个数

	return;
}


/*
* 函数名称：BuildNodeChildren
* 描    述：通过接收的数组创建结点的孩子结点
* 函数输入：pTreeRoot根节点，arrayData编码数组，arrayScore分数数组，arrayLength数组长度
* 函数输出：pTreeRoot根结点的指针
* 调用函数：InsertNode、CreateNode、SearchDataByBFS
*/
PNODE BuildNodeChildren(PNODE pTreeRoot, int *arrayData, int *arrayScore, int arrayLength)
{
	PNODE pTem = NULL;//中间变量

	if (NULL == pTreeRoot)//表明该数组是传回的第一个数组
	{
		pTreeRoot = CreateNode(arrayData[0], arrayScore[0]);	//先创建根结点
		pTem = pTreeRoot;
	}
	else
	{
		pTem = SearchDataByBFS(pTreeRoot, arrayData[0]);//找到要插入新结点的父结点
	}

	//向根节点中插入arrayLength-1个孩子结点
	//注意0号元素是父结点，之后的元素才是孩子结点
	for (int i = 1; i < arrayLength; i++)//注意是从下标为1的元素开始创建新节点并插入
	{
		PNODE pNew = CreateNode(arrayData[i], arrayScore[i]);	//创建新节点
		InsertNode(pTem, pNew);	//插入父结点（注意不一定是根节点）下
	}

	return pTreeRoot;
}

/*
* 函数名称：SearchNodeByScore
* 描    述：按分数搜索搜索树的根结点的孩子结点
		    【注意】此函数只搜索根节点的孩子结点，不搜索其他结点
* 函数输入：PNODE pTreeRoot树的根结点, int GoalScore目标结点的分数
* 函数输出：PNODE pTemNode目标树结点的指针
* 调用函数：无
*/
PNODE SearchNodeByScore(PNODE pTreeRoot, int goalScore)
{
	//对树的根结点的孩子做搜索操作	
	//访问根结点的下一层
	PLISTNODE pTemListNode = pTreeRoot->m_pChildList->m_pNext;	//指向链表的首结点，头结点不用
	while ((NULL != pTemListNode) && (goalScore != pTemListNode->m_pNodeAddress->m_score))
	{
		pTemListNode = pTemListNode->m_pNext;	//指向下一个链表结点
	}
	//循环结束后，有两种情况
	//情况1：查找到目标孩子结点
	if (NULL != pTemListNode)
	{
		PNODE pTemNode = pTemListNode->m_pNodeAddress;
		return pTemNode;	//返回树中的目标结点的指针
	}
	//情况2：不存在这样分数的结点，即没查找到目标结点
	else
	{
		return NULL;
	}
}

/*
* 函数名称：DestorySubtree
* 描    述：删除当前结点及其子树
*			如果需要释放整棵树，只需要将 pTem 赋值为根结点 pTreeRoot
* 函数输入：PNODE pTem要删除的树结点
*		    其中 pTem 可以这样的到：PNODE pTem = SearchNodeByData(pTreeRoot, GoalScore);	//查找到目标结点
* 函数输出：pTreeRoot根结点的指针
* 调用函数：无
*/
void DestorySubtree(PNODE pTem)
{
	PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//指向首结点
	//如果树结点的“孩子结点链表”非空，则需要依次删除每一个指针指向的孩子结点
	if (NULL != pTemListNode)
	{
		//依次删除链表结点对应的每一个孩子结点
		//当孩子指针指向的孩子结点非空时
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			DestorySubtree(pTemListNode->m_pNodeAddress);	//递归删除孩子结点
			pTemListNode = pTemListNode->m_pNext;	//指向链表的下一个结点
		}
		//释放当前结点的指针链表
		PLISTNODE pListHead = pTem->m_pChildList;	//指向链表的头结点
		while (NULL != pListHead->m_pNext)
		{
			DeleteListNode(pListHead);	//循环删除首结点，直到没有首结点为止
		}

	}

	//如果树结点的“孩子结点链表”为空，也就是没有孩子结点
	//先释放空链表的头结点
	delete pTem->m_pChildList;
	pTem->m_pChildList = NULL;

	//再释放孩子结点的空间
	delete pTem;
	pTem = NULL;
	
	return;
}

/*
* 函数名称：PrintTreeData
* 描    述：打印树的编号
* 函数输入：PNODE pTreeRoot树的根结点, int GoalScore目标结点的分数
* 函数输出：目标树结点的指针
* 调用函数：无
*/
void PrintTreeData(PNODE pTreeRoot)
{
	//从根结点开始访问
	PNODE pTem = pTreeRoot;	//初始化当前结点
	//如果当前结点不是空结点
	if (NULL != pTem)
	{
		cout << pTem->m_data << "\t";
	}
	
	PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//指向链表的首结点
	//如果当前链表有孩子结点
	while (NULL != pTemListNode)
	{
		PNODE pTemNode = pTemListNode->m_pNodeAddress;	//当前链表结点指向的孩子结点
		//对孩子结点进行递归输出
		PrintTreeData(pTemNode);
		pTemListNode = pTemListNode->m_pNext;	//指向链表的下一个结点
	}

	return;
}

/*
* 函数名称：BFSTraverse
* 描    述：广度优先遍历，也就是树的层序遍历
* 输入参数：PNODE pStartNode遍历的起始结点，不局限于根结点
* 输出参数：无
* 调用函数：无
*/
void BFSTraverse(PNODE pStartNode)
{
	queue<PNODE> myQueue;	//创建一个PNODE型的队列

	myQueue.push(pStartNode);	//将起始结点的成员变量m_data入队，也可以存地址
	//如果队列非空表示还有结点的孩子结点等待访问，此结点的孩子结点可为空
	while (!myQueue.empty())
	{
		//获取队首的结点指针
		PNODE pTemNode = myQueue.front();	//读取队首元素，不删除队中数据
		cout << pTemNode->m_data << "\t";	//输出当前结点
		myQueue.pop();	//出队，没有返回值

		//判断当前结点是否有孩子
		PLISTNODE pTemListNode = pTemNode->m_pChildList->m_pNext;	//指向当前结点的成员中，链表的首结点
		//如果当前结点有孩子结点
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			myQueue.push(pTemListNode->m_pNodeAddress);	//将子节点入队
			pTemListNode = pTemListNode->m_pNext;	//指向下一个结点
		}

	}
	cout << endl;	//遍历结束

	return;
}

/*
* 函数名称：SearchDataByBFS
* 描    述：基于广度优先遍历的树的目标结点搜索
* 输入参数：PNODE pStartNode遍历的起始结点，不局限于根结点；int goalData目标编号
* 输出参数：PNODE pTemNode目标结点的指针
* 调用函数：无
*/
PNODE SearchDataByBFS(PNODE pStartNode, int goalData)
{
	queue<PNODE> myQueue;	//创建一个PNODE型的队列

	myQueue.push(pStartNode);	//将起始结点的成员变量m_data入队，也可以存地址
								//如果队列非空表示还有结点的孩子结点等待访问，此结点的孩子结点可为空
	while (!myQueue.empty())
	{
		//获取队首的结点指针
		PNODE pTemNode = myQueue.front();	//读取队首元素，不删除队中数据
		myQueue.pop();	//出队，没有返回值

		//判断当前结点是否为目标结点
		//如果当前结点是目标结点
		if ((NULL != pTemNode) && (goalData == pTemNode->m_data))
		{
			return pTemNode;	//结束函数
		}

		//判断当前结点是否有孩子
		PLISTNODE pTemListNode = pTemNode->m_pChildList->m_pNext;	//指向当前结点的成员中，链表的首结点
																	//如果当前结点有孩子结点
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			myQueue.push(pTemListNode->m_pNodeAddress);	//将子节点入队
			pTemListNode = pTemListNode->m_pNext;	//指向下一个结点
		}
	}
	//遍历结束，未查找到目标结点
	return NULL;
}

/*
* 函数名称：ModifyNodeScore
* 描    述：修改目标结点的评估分数
* 输入参数：PNODE pStartNode搜索的起始结点,int goalData目标编号, int modifiedSorce修改后的分数
* 输出参数：无
* 调用函数：无
*/
void ModifyNodeScore(PNODE pStartNode, int goalData, int modifiedSorce)
{
	//查找目标编号额结点
	PNODE pTemNode = SearchDataByBFS(pStartNode, goalData);

	if (NULL == pTemNode)
	{
		cout << "不存在目标结点!" << endl;
	}
	else
	{
		//修改当前结点的评估分值
		pTemNode->m_score = modifiedSorce;
	}
	

	return;
}