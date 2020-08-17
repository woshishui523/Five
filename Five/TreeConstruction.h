/*
* �ļ����ƣ�TreeConstruction.h
* ժ    Ҫ�����Ľ��Ķ���
*
* ��ǰ�汾���汾3.0
* ��    �ߣ�LiuRuiGuang && WuYue
* ���ʱ�䣺2020��8��8��
*/

#pragma once
#ifndef TreeConstruction_H
#define TreeConstruction_H

//���Ľ��
typedef struct Node
{
	int m_data;	//�����򣬿��Ը��������޸ĳ���Ҫ���������ͣ�Ҳ����������
	int m_score;	//����������������ǰ��������λ�õ����ȼ�
	//ָ����
	struct Node *m_pParent;	//����㣨����㣩ָ��
	int m_ChildNum;	//���ӽ��ĸ�������������Ч�ڵ�ĳ���
	struct ListNode *m_pChildList;	//ָ�򡰴洢���ӽ��ָ��������ͷ���
	struct ListNode *m_pListTail;	//ָ�������β���
}NODE, *PNODE, **PPNODE;

//����ָ������Ľ��
typedef struct ListNode
{
	PNODE m_pNodeAddress;	//�������������ָ�����ĺ��ӽ���ָ��
	struct ListNode *m_pNext;	//�������ָ����ָ����һ���������ָ��	
}LISTNODE, *PLISTNODE;

//������������
PLISTNODE CreateListNode(PNODE pChild);	//����ͨ�õ�������
PLISTNODE CreateList(void);	//����һ��������
PLISTNODE InsertListNodeByTail(PLISTNODE pTail, PLISTNODE pNew);	//β�巨��������Ľ��
void DeleteListNode(PLISTNODE pHead, int score);	//ɾ��������
PNODE CreateNode(int data, int score);	//��������ͨ�ý��
PNODE SearchNodeByData(PNODE pTreeRoot, int goalData);	//����Ŀ����
void InsertNode(PNODE pTem, PNODE pNew);	//�����㣬�� pTem �У����� pNew
PNODE BuildNodeChildren(PNODE pTreeRoot, int *arrayData, int *arrayScore, int arrayLength);	//ͨ�����鴴�����ĺ��ӽ��
PNODE SearchNodeByScore(PNODE pTreeRoot, int goalScore);	//����Ŀ�������
void DestorySubtree(PNODE pTem);	//ɾ����ǰ��㼰�����������������ͷ���������Ҳ���Բü�������ķ�֧
void PrintTreeData(PNODE pTreeRoot);	//������ȱ��������Գ���ʹ��
void BFSTraverse(PNODE pStartNode);	//������ȱ��������Գ���ʹ��
PNODE SearchDataByBFS(PNODE pStartNode, int goalData);	//����BFS��Ŀ��������
void ModifyNodeScore(PNODE pStartNode, int goalData, int modifiedSorce);	//ͨ����Ų��ң����޸�Ŀ����ķ�ֵ

#endif