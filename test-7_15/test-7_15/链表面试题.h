#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
	int val;
	struct CNode *random;
	struct CNode *next;
}	CNode;

// ���д� random ָ�������ĸ���
CNode * copy(CNode * head) {
	/*
	��ÿ����㣨�Ͻ�㣩���Ƴ�һ����㣨�½�㣩
	���½������Ͻ��ĺ��
	*/

	CNode * cur = head;
	while (cur != NULL) {
		// �ȸ����½��
		CNode * node = (CNode *)malloc(sizeof(CNode));
		node->val = cur->val;

		// ���½��(node)�����Ͻ��(cur)���
		node->next = cur->next;
		cur->next = node;

		// �������� cur ָ����һ���Ͻ��
		cur = node->next;
	}

	/*
	���� random �ĸ���
	cur ָ��ÿһ���Ͻ��
	*/
	cur = head;
	while (cur != NULL) {
		// cur->next ���� cur ��Ӧ���½��
		if (cur->random != NULL) {
			cur->next->random = cur->random->next;
		}
		else {
			cur->next->random = NULL;
		}

		cur = cur->next->next;
	}

	/*
	���������µĺ��ϵ�
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