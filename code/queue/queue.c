#include "queue.h"

ROOT* newQueue(){
	ROOT* r = NULL;
	if( !(r = (ROOT*) malloc(sizeof(ROOT)))){
		/* print to the error right here */
		fprintf(stderr, "Failed to allocate memory for a new Queue.");
		exit(1);
	}
	r->first = NULL;
	r->last = NULL;
	r->elements = 0;
	return r;
}

void push(ROOT* r, void* v){
	QUEUENODE* newMember = NULL;
	/* allocate memory */
	if(!(newMember = (QUEUENODE*) malloc(sizeof(QUEUENODE)))){
		/* output into the error message here */
		fprintf(stderr, "Failed to allocate memory for a new node.");
		exit(2);
	}
	/* construct the new node */
	newMember->value = v;
	newMember->next=NULL;
	/* push the new node onto the list */
	if(r->first==NULL){
		r->first = newMember;
		r->last = newMember;
	} else {
		QUEUENODE* node = r->last;
		node->next = newMember;
		r->last = newMember;
	}
	r->elements++;
	return;
}

void* pop(ROOT* r){
	QUEUENODE* node = r->first;
	if(node == NULL){
		fprintf(stderr, "Tried to pop an empty queue.");
		/* print ot the error stream */
		exit(3);
	}
	void* v = node->value;
	r->first = node->next;
	free(node);
	r->elements--;
	return v;
} 

void emptyQueue(ROOT* r){
    void* v;
    while(1){
        if(r->first == NULL) break;
        v = pop(r);
        free(v);
    }
    free(r);
}

bool isEmpty(ROOT* r){
	if(r->first == NULL){
		return true;
	} else {
		return false;
	}
}