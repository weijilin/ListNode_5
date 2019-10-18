#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
	int val;
	struct CNode *random;
	struct CNode *next;
}	CNode;

// 进行带 random 指针的链表的复制
CNode * copy(CNode * head) {
	/*
	把每个结点（老结点）复制出一个结点（新结点）
	让新结点跟在老结点的后边
	*/

	CNode * cur = head;
	while (cur != NULL) {
		// 先复制新结点
		CNode * node = (CNode *)malloc(sizeof(CNode));
		node->val = cur->val;

		// 让新结点(node)跟在老结点(cur)后边
		node->next = cur->next;
		cur->next = node;

		// 遍历，让 cur 指向下一个老结点
		cur = node->next;
	}

	/*
	进行 random 的复制
	cur 指向每一个老结点
	*/
	cur = head;
	while (cur != NULL) {
		// cur->next 就是 cur 对应的新结点
		if (cur->random != NULL) {
			cur->next->random = cur->random->next;
		}
		else {
			cur->next->random = NULL;
		}

		cur = cur->next->next;
	}

	/*
	把链表拆分新的和老的
	*/
	cur = head;
	CNode *newHead = head->next;
	while (cur != NULL) {
		CNode *node = cur->next;

		cur->next = node->next;
		if (node->next != NULL) {
			node->next = node->next->next;
		}

		cur = cur->next;
	}

	return newHead;
}

CNode * createNode(int val) {
	CNode * node = (CNode *)malloc(sizeof(CNode));
	node->val = val;

	return node;
}

void test() {
	CNode *n1 = createNode(1);
	CNode *n2 = createNode(2);
	CNode *n3 = createNode(3);
	CNode *n4 = createNode(4);
	CNode *n5 = createNode(5);

	n1->next = n2; n2->next = n3; n3->next = n4;
	n4->next = n5; n5->next = NULL;

	n1->random = n3; n2->random = n1; n3->random = n4;
	n4->random = n4; n5->random = NULL;

	CNode *result = copy(n1);

	for (CNode * cur = n1; cur != NULL; cur = cur->next) {
		printf("%p(%d, %p) ", cur, cur->val, cur->random);
	}
	printf("\n");

	for (CNode * cur = result; cur != NULL; cur = cur->next) {
		printf("%p(%d, %p) ", cur, cur->val, cur->random);
	}
	printf("\n");
}