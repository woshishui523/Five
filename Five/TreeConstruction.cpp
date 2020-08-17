/*
* �ļ����ƣ�TreeConstruction.cpp
* ժ    Ҫ��������������ʵ���ļ�
*
* ��ǰ�汾���汾3.0
* �޸����ݣ����ӹ�����ȱ�������			BFSTraverse
*			���ӻ���BFS��Ŀ����������		SearchDataByBFS
*			����Ŀ����ķ�ֵ�޸ĺ���	    ModifyNodeScore
*			�޸����Ĵ�������Ϊ��Ӻ��Ӻ���  BuildNodeChildren
* ��ʷ�汾���汾2.0
* �޸����ݣ�����ע�͡��޸ı������ơ����Ӻ��ӽ���������
* ��ʷ�汾���汾1.0
*
* ��    �ߣ�LiuRuiGuang && WuYue
* ���ʱ�䣺2020��8��8��
*/


#include <iostream>
using namespace std;
#include <queue>	//ʹ��STL�еĶ���
#include "TreeConstruction.h"

/*
* �������ƣ�CreateListNode
* ��    ��������������
* �������룺PNODE pChild������������ӽ���ָ��
* ���������PLISTNODE pNewListNode�������ָ��
* ���ú�������
*/
PLISTNODE CreateListNode(PNODE pChild)
{
	PLISTNODE pNewListNode = new LISTNODE;	//�½�һ������Ľ��
	if (NULL == pNewListNode)
	{
		cout << "����ʧ�ܣ�������ֹ��" << endl;
		exit(-1);	//�쳣�˳�
	}
	//����ɹ�
	pNewListNode->m_pNodeAddress = pChild;	//�����ĺ���ָ�븳ֵ���������������
	pNewListNode->m_pNext = NULL;	//�������ָ������ʼ��

	return pNewListNode;	//�����½����ĵ�ַ
}

/*
* �������ƣ�CreateList
* ��    ����ʹ�ö�̬����ķ�������һ��������
* �������룺��
* ���������PLISTNODE pHeadListNode�����ض�̬�����ͷ���ĵ�ַ
* ���ú�������
*/
PLISTNODE CreateList(void)
{
	PLISTNODE pHeadListNode = new LISTNODE;	//����һ��ͷ���
	if (NULL == pHeadListNode)//�ж�ͷ�ڵ��Ƿ����ɹ�
	{
		cout << "����ʧ�ܣ�������ֹ��" << endl;
		exit(-1);	//�쳣�˳�
	}
	else
	{
		pHeadListNode->m_pNodeAddress = NULL;
		pHeadListNode->m_pNext = NULL;	
		return pHeadListNode;	//����ɹ�������ͷ���
	}
}


/*
* �������ƣ�InsertListNodeByTail
* ��    ����β�巨,�������в�������Ľ��
* �������룺PLISTNODE pListTail�����βָ��, PLISTNODE pListNew���������������
* ���������pListTail���ص�ǰ�����βָ��
* ���ú�������
*/
PLISTNODE InsertListNodeByTail(PLISTNODE pListTail, PLISTNODE pListNew)
{
	pListTail->m_pNext = pListNew;	//�������ɵ�������ҵ�ԭ������
	pListNew->m_pNext = NULL;	//β����ָ����ʼ��Ϊ��
	pListTail = pListNew;	//βָ��ʼ��ָ��β���

	return pListTail;
}

/*
* �������ƣ�DeleteListNode
* ��    ����������ɾ������Ľ��
* �������룺PLISTNODE pListFrontҪɾ��������Ŀ�����ǰһ�����
* �����������
* ���ú�������
*/
void DeleteListNode(PLISTNODE pListFront)
{
	PLISTNODE pListTem = pListFront->m_pNext;	//Ҫɾ���������Ŀ����

	//ɾ��Ŀ��������
	//����ǰ�����㡱ǰһ������ָ�룬ָ�򡰵�ǰ�����㡱����һ����㣬�����ǰ���
	pListFront->m_pNext = pListTem->m_pNext;

	delete pListTem;	//�ͷŵ�ǰ������Ŀռ�
	pListTem = NULL;

	return;
}



/*
* �������ƣ�CreateNode
* ��    �����������Ľ�㣬��ͨ���βν��յĲ�����ʼ�������ĳ�Ա����
* �������룺int data���ױ���, int score�����ķ�ֵ
* ���������PNODE pNew�½��������ָ��
* ���ú�����CreateList����������
*/
PNODE CreateNode(int data, int score)
{
	PNODE pNew = new NODE;	//�ڶ��д���һ�����

	if (NULL == pNew)	//����ռ����ʧ��
	{
		cout << "score����������������룡" << endl;
		exit(-1);	//�쳣�˳�
	}
	else  //��㴴���ɹ�
	{
		pNew->m_data = data;	//�洢���ӵ�λ��
		pNew->m_score = score;//�洢����
		pNew->m_ChildNum = 0;	//��ʼ�����ӽ��ĸ���
		//�����ĸ����ָ��
		pNew->m_pParent = NULL;	//����Ұָ��

		//����һ������ָ�������
		pNew->m_pChildList = CreateList();	//�ȴ���һ��������
		pNew->m_pListTail = pNew->m_pChildList;	//�������β������ͷ���
	}

	return pNew;	//�����½����ĵ�ַ
}

/*
* �������ƣ�SearchNodeByData
* ��    ��������ÿһʱ�����̵ı��룬����������Ŀ���㣬�����ؽ��ָ��
			������ʽ���������
* �������룺PNODE pTemNode��������ʼ���, int goalDataĿ����ķ���
* ���������PNODE tempĿ��������ָ��
* ���ú�����SearchNodeByData�ݹ����
*/
PNODE SearchNodeByData(PNODE pTreeRoot, int goalData)
{
	//�Ӹ���㿪ʼ����
	PNODE pTem = pTreeRoot;	//��ʼ����ǰ���
	PNODE temp = NULL;
	//�����ǰ�����Ŀ����
	if ((NULL != pTem) && (goalData == pTem->m_data))
	{
		temp = pTem;
	}
	else //��ǰ��㲻��Ŀ����
	{
		//�ڵ�ǰ��㲻��Ŀ���㣬���������ĺ���
		PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//ָ��������׽��
		//���������������к��ӽ��
		//�����ǰ������ǿգ���ʾ�к��ӽ�㣬�����ѭ��
		while (NULL != pTemListNode)
		{
			PNODE pTemNode = pTemListNode->m_pNodeAddress;	//��ǰ��������ָ��ĺ��ӽ��
			//�Ըú��ӽ����еݹ�����
			temp = SearchNodeByData(pTemNode, goalData);
			//���������Ŀ���㣬�����ѭ���ݹ�
			if (NULL != temp)
			{
				break;	//����ѭ��
			}
			pTemListNode = pTemListNode->m_pNext;	//ָ���������һ�����
		}

	}

	return temp;	//����Ŀ�����ָ��
}


/*
* �������ƣ�InsertNode
* ��    ��������һ�������
* �������룺PNODE pTem������������, PNODE pNew�������µ������
* �����������
* ���ú�������
*/
void InsertNode(PNODE pTem, PNODE pNew) 
{
	PLISTNODE pListTail = pTem->m_pListTail;	//��ǰ���ĺ��ӽ�������βָ��

	PLISTNODE pListNew = CreateListNode(pNew);	//ͨ���µ�����㴴��һ��������
	//���½����ͨ��β�巨�����뵱ǰ�Ľ����
	pTem->m_pListTail = InsertListNodeByTail(pListTail, pListNew);	//�����ӽ���ָ�����������

	pNew->m_pParent = pTem;	//���¸����ָ��
	(pTem->m_ChildNum)++;	//���±�������ĺ��ӽ��ĸ���

	return;
}


/*
* �������ƣ�BuildNodeChildren
* ��    ����ͨ�����յ����鴴�����ĺ��ӽ��
* �������룺pTreeRoot���ڵ㣬arrayData�������飬arrayScore�������飬arrayLength���鳤��
* ���������pTreeRoot������ָ��
* ���ú�����InsertNode��CreateNode��SearchDataByBFS
*/
PNODE BuildNodeChildren(PNODE pTreeRoot, int *arrayData, int *arrayScore, int arrayLength)
{
	PNODE pTem = NULL;//�м����

	if (NULL == pTreeRoot)//�����������Ǵ��صĵ�һ������
	{
		pTreeRoot = CreateNode(arrayData[0], arrayScore[0]);	//�ȴ��������
		pTem = pTreeRoot;
	}
	else
	{
		pTem = SearchDataByBFS(pTreeRoot, arrayData[0]);//�ҵ�Ҫ�����½��ĸ����
	}

	//����ڵ��в���arrayLength-1�����ӽ��
	//ע��0��Ԫ���Ǹ���㣬֮���Ԫ�ز��Ǻ��ӽ��
	for (int i = 1; i < arrayLength; i++)//ע���Ǵ��±�Ϊ1��Ԫ�ؿ�ʼ�����½ڵ㲢����
	{
		PNODE pNew = CreateNode(arrayData[i], arrayScore[i]);	//�����½ڵ�
		InsertNode(pTem, pNew);	//���븸��㣨ע�ⲻһ���Ǹ��ڵ㣩��
	}

	return pTreeRoot;
}

/*
* �������ƣ�SearchNodeByScore
* ��    ���������������������ĸ����ĺ��ӽ��
		    ��ע�⡿�˺���ֻ�������ڵ�ĺ��ӽ�㣬�������������
* �������룺PNODE pTreeRoot���ĸ����, int GoalScoreĿ����ķ���
* ���������PNODE pTemNodeĿ��������ָ��
* ���ú�������
*/
PNODE SearchNodeByScore(PNODE pTreeRoot, int goalScore)
{
	//�����ĸ����ĺ�������������	
	//���ʸ�������һ��
	PLISTNODE pTemListNode = pTreeRoot->m_pChildList->m_pNext;	//ָ��������׽�㣬ͷ��㲻��
	while ((NULL != pTemListNode) && (goalScore != pTemListNode->m_pNodeAddress->m_score))
	{
		pTemListNode = pTemListNode->m_pNext;	//ָ����һ��������
	}
	//ѭ�����������������
	//���1�����ҵ�Ŀ�꺢�ӽ��
	if (NULL != pTemListNode)
	{
		PNODE pTemNode = pTemListNode->m_pNodeAddress;
		return pTemNode;	//�������е�Ŀ�����ָ��
	}
	//���2�����������������Ľ�㣬��û���ҵ�Ŀ����
	else
	{
		return NULL;
	}
}

/*
* �������ƣ�DestorySubtree
* ��    ����ɾ����ǰ��㼰������
*			�����Ҫ�ͷ���������ֻ��Ҫ�� pTem ��ֵΪ����� pTreeRoot
* �������룺PNODE pTemҪɾ���������
*		    ���� pTem ���������ĵ���PNODE pTem = SearchNodeByData(pTreeRoot, GoalScore);	//���ҵ�Ŀ����
* ���������pTreeRoot������ָ��
* ���ú�������
*/
void DestorySubtree(PNODE pTem)
{
	PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//ָ���׽��
	//��������ġ����ӽ�������ǿգ�����Ҫ����ɾ��ÿһ��ָ��ָ��ĺ��ӽ��
	if (NULL != pTemListNode)
	{
		//����ɾ���������Ӧ��ÿһ�����ӽ��
		//������ָ��ָ��ĺ��ӽ��ǿ�ʱ
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			DestorySubtree(pTemListNode->m_pNodeAddress);	//�ݹ�ɾ�����ӽ��
			pTemListNode = pTemListNode->m_pNext;	//ָ���������һ�����
		}
		//�ͷŵ�ǰ����ָ������
		PLISTNODE pListHead = pTem->m_pChildList;	//ָ�������ͷ���
		while (NULL != pListHead->m_pNext)
		{
			DeleteListNode(pListHead);	//ѭ��ɾ���׽�㣬ֱ��û���׽��Ϊֹ
		}

	}

	//��������ġ����ӽ������Ϊ�գ�Ҳ����û�к��ӽ��
	//���ͷſ������ͷ���
	delete pTem->m_pChildList;
	pTem->m_pChildList = NULL;

	//���ͷź��ӽ��Ŀռ�
	delete pTem;
	pTem = NULL;
	
	return;
}

/*
* �������ƣ�PrintTreeData
* ��    ������ӡ���ı��
* �������룺PNODE pTreeRoot���ĸ����, int GoalScoreĿ����ķ���
* ���������Ŀ��������ָ��
* ���ú�������
*/
void PrintTreeData(PNODE pTreeRoot)
{
	//�Ӹ���㿪ʼ����
	PNODE pTem = pTreeRoot;	//��ʼ����ǰ���
	//�����ǰ��㲻�ǿս��
	if (NULL != pTem)
	{
		cout << pTem->m_data << "\t";
	}
	
	PLISTNODE pTemListNode = pTem->m_pChildList->m_pNext;	//ָ��������׽��
	//�����ǰ�����к��ӽ��
	while (NULL != pTemListNode)
	{
		PNODE pTemNode = pTemListNode->m_pNodeAddress;	//��ǰ������ָ��ĺ��ӽ��
		//�Ժ��ӽ����еݹ����
		PrintTreeData(pTemNode);
		pTemListNode = pTemListNode->m_pNext;	//ָ���������һ�����
	}

	return;
}

/*
* �������ƣ�BFSTraverse
* ��    ����������ȱ�����Ҳ�������Ĳ������
* ���������PNODE pStartNode��������ʼ��㣬�������ڸ����
* �����������
* ���ú�������
*/
void BFSTraverse(PNODE pStartNode)
{
	queue<PNODE> myQueue;	//����һ��PNODE�͵Ķ���

	myQueue.push(pStartNode);	//����ʼ���ĳ�Ա����m_data��ӣ�Ҳ���Դ��ַ
	//������зǿձ�ʾ���н��ĺ��ӽ��ȴ����ʣ��˽��ĺ��ӽ���Ϊ��
	while (!myQueue.empty())
	{
		//��ȡ���׵Ľ��ָ��
		PNODE pTemNode = myQueue.front();	//��ȡ����Ԫ�أ���ɾ����������
		cout << pTemNode->m_data << "\t";	//�����ǰ���
		myQueue.pop();	//���ӣ�û�з���ֵ

		//�жϵ�ǰ����Ƿ��к���
		PLISTNODE pTemListNode = pTemNode->m_pChildList->m_pNext;	//ָ��ǰ���ĳ�Ա�У�������׽��
		//�����ǰ����к��ӽ��
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			myQueue.push(pTemListNode->m_pNodeAddress);	//���ӽڵ����
			pTemListNode = pTemListNode->m_pNext;	//ָ����һ�����
		}

	}
	cout << endl;	//��������

	return;
}

/*
* �������ƣ�SearchDataByBFS
* ��    �������ڹ�����ȱ���������Ŀ��������
* ���������PNODE pStartNode��������ʼ��㣬�������ڸ���㣻int goalDataĿ����
* ���������PNODE pTemNodeĿ�����ָ��
* ���ú�������
*/
PNODE SearchDataByBFS(PNODE pStartNode, int goalData)
{
	queue<PNODE> myQueue;	//����һ��PNODE�͵Ķ���

	myQueue.push(pStartNode);	//����ʼ���ĳ�Ա����m_data��ӣ�Ҳ���Դ��ַ
								//������зǿձ�ʾ���н��ĺ��ӽ��ȴ����ʣ��˽��ĺ��ӽ���Ϊ��
	while (!myQueue.empty())
	{
		//��ȡ���׵Ľ��ָ��
		PNODE pTemNode = myQueue.front();	//��ȡ����Ԫ�أ���ɾ����������
		myQueue.pop();	//���ӣ�û�з���ֵ

		//�жϵ�ǰ����Ƿ�ΪĿ����
		//�����ǰ�����Ŀ����
		if ((NULL != pTemNode) && (goalData == pTemNode->m_data))
		{
			return pTemNode;	//��������
		}

		//�жϵ�ǰ����Ƿ��к���
		PLISTNODE pTemListNode = pTemNode->m_pChildList->m_pNext;	//ָ��ǰ���ĳ�Ա�У�������׽��
																	//�����ǰ����к��ӽ��
		while ((NULL != pTemListNode) && (NULL != pTemListNode->m_pNodeAddress))
		{
			myQueue.push(pTemListNode->m_pNodeAddress);	//���ӽڵ����
			pTemListNode = pTemListNode->m_pNext;	//ָ����һ�����
		}
	}
	//����������δ���ҵ�Ŀ����
	return NULL;
}

/*
* �������ƣ�ModifyNodeScore
* ��    �����޸�Ŀ�������������
* ���������PNODE pStartNode��������ʼ���,int goalDataĿ����, int modifiedSorce�޸ĺ�ķ���
* �����������
* ���ú�������
*/
void ModifyNodeScore(PNODE pStartNode, int goalData, int modifiedSorce)
{
	//����Ŀ���Ŷ���
	PNODE pTemNode = SearchDataByBFS(pStartNode, goalData);

	if (NULL == pTemNode)
	{
		cout << "������Ŀ����!" << endl;
	}
	else
	{
		//�޸ĵ�ǰ����������ֵ
		pTemNode->m_score = modifiedSorce;
	}
	

	return;
}