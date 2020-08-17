/*
* 文件名称：TreeConstruction.h
* 摘    要：树的结点的定义
*
* 当前版本：版本3.0
* 作    者：LiuRuiGuang && WuYue
* 完成时间：2020年8月8日
*/

#pragma once
#ifndef TreeConstruction_H
#define TreeConstruction_H

//树的结点
typedef struct Node
{
	int m_data;	//数据域，可以根据需求修改成需要的数据类型，也可以是数组
	int m_score;	//分数，用来衡量当前棋子落子位置的优先级
	//指针域
	struct Node *m_pParent;	//父结点（树结点）指针
	int m_ChildNum;	//孩子结点的个数，即链表有效节点的长度
	struct ListNode *m_pChildList;	//指向“存储孩子结点指针链表”的头结点
	struct ListNode *m_pListTail;	//指向链表的尾结点
}NODE, *PNODE, **PPNODE;

//孩子指针链表的结点
typedef struct ListNode
{
	PNODE m_pNodeAddress;	//链表结点的数据域，指向树的孩子结点的指针
	struct ListNode *m_pNext;	//链表结点的指针域，指向下一个链表结点的指针	
}LISTNODE, *PLISTNODE;

//基本操作函数
PLISTNODE CreateListNode(PNODE pChild);	//创建通用的链表结点
PLISTNODE CreateList(void);	//创建一个空链表
PLISTNODE InsertListNodeByTail(PLISTNODE pTail, PLISTNODE pNew);	//尾插法插入链表的结点
void DeleteListNode(PLISTNODE pHead, int score);	//删除链表结点
PNODE CreateNode(int data, int score);	//创建树的通用结点
PNODE SearchNodeByData(PNODE pTreeRoot, int goalData);	//查找目标结点
void InsertNode(PNODE pTem, PNODE pNew);	//插入结点，在 pTem 中，插入 pNew
PNODE BuildNodeChildren(PNODE pTreeRoot, int *arrayData, int *arrayScore, int arrayLength);	//通过数组创建结点的孩子结点
PNODE SearchNodeByScore(PNODE pTreeRoot, int goalScore);	//搜索目标树结点
void DestorySubtree(PNODE pTem);	//删除当前结点及其子树，可以用来释放整棵树，也可以裁剪多叉树的分支
void PrintTreeData(PNODE pTreeRoot);	//深度优先遍历，测试程序使用
void BFSTraverse(PNODE pStartNode);	//广度优先遍历，测试程序使用
PNODE SearchDataByBFS(PNODE pStartNode, int goalData);	//基于BFS的目标结点搜索
void ModifyNodeScore(PNODE pStartNode, int goalData, int modifiedSorce);	//通过编号查找，并修改目标结点的分值

#endif