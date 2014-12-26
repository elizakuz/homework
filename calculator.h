typedef struct node_t{
	int v;
	struct node_t * next;
} node_t;
typedef struct int_list {
	size_t count;
	node_t * head;
} int_list;
typedef struct long_num {
	int sign;
	int_list digits;
} long_num;
void add(int n, int_list * l){
	node_t *p = (node_t *) malloc(sizeof (node_t));
	p->v = n;
	p->next = l->head;
	l->head = p;	
}
void print(node_t * hd){
	node_t * p = hd;
     	for(;p != NULL; p = p->next){
		printf("%d", p->v);
		
	}		
}
long_num long_numCreate(char c) {
	long_num x;
	x.digits.head = NULL;
	x.sign = 1;
	int_list l;
	l.count = 0;
	l.head = NULL;	
	while (c != 13) {
		add(c - '0', &l);
		l.count++;
		c = getchar();
	}
	x.digits = l;
	return x;
}
int_list long_numReverse(int_list x) {
	node_t * r = x.head;
	int i;
	int_list k;
	k.head= NULL;
	for (i = 0; i < x.count; i++) {
		add(r->v, &k);	
		r = r->next;
	}
	k.count = x.count;
	return k;
}
long_num long_numAdd(long_num x, long_num y) {
	long_num sum;
	sum.digits.head = NULL;
	int ost = 0;
	int s;
	long_num z;
	sum.digits.count = 0;
	if (x.digits.count < y.digits.count) {
		z = x;
		x = y;
		y = z;
	}
	for (y.digits.count; y.digits.count != 0; y.digits.count--, x.digits.count--) {
		s = (x.digits.head->v + y.digits.head->v + ost) % 10;
		ost = (x.digits.head->v + y.digits.head->v + ost) / 10;
		add(s, &sum.digits);
		free(x.digits.head);
		x.digits.head = x.digits.head->next;
		free(y.digits.head);
		y.digits.head = y.digits.head->next;
		sum.digits.count++;
	}
	for (x.digits.count; x.digits.count != 0; x.digits.count--) {
		s = (x.digits.head->v + ost) % 10;
		add(s, &sum.digits);
		ost = (x.digits.head->v + ost) / 10;
		free(x.digits.head);
		x.digits.head = x.digits.head->next;
		sum.digits.count++;
	}
	if (ost == 1 ) {
		add(1, &sum.digits);
		sum.digits.count++;
	}
	sum.sign = x.sign;
	return sum;
}
long_num long_numSub(long_num x, long_num y) {
	int zn = x.sign;
	long_num sub;
	sub.digits.head = NULL;
	sub.digits.count = 0;
	int ost = 0;
	int m;
	long_num z;
	if (x.digits.count < y.digits.count) {
		z = x;
		x = y;
		y = z;
		zn *= -1;
	}
	if (x.digits.count == y.digits.count) {
		int_list x2, y2;
		int i;
		x2 = long_numReverse(x.digits);
		y2 = long_numReverse(y.digits);
		node_t * p = x2.head;
		node_t * q = y2.head;
		for (i = 0; i < x2.count; i++) {
			if (p->v > q->v) {
				break;
			}
			if (p->v < q->v) {
				z = x;
				x = y;
				y = z;
				zn *= -1;
				break;
			}	
			p = p->next;	 	
			q = q->next;
		}
	}
	node_t * p = y.digits.head;
	for (y.digits.count; y.digits.count != 0; y.digits.count--, x.digits.count--) {
		m = x.digits.head->v - p->v - ost;
		if (m < 0) {
			ost = 1;
			m += 10;
		} else {
			ost = 0;
		}	
		add(m, &sub.digits);
		free(x.digits.head);
		x.digits.head = x.digits.head->next;
		p = p->next;
		sub.digits.count++;
	}
	for (x.digits.count; x.digits.count != 0; x.digits.count--) {
		m = x.digits.head->v - ost;
		if (m < 0) {
			ost = 1;
			m += 10;
		} else {
			ost = 0;
		}
		add(m, &sub.digits);
		free(x.digits.head);
		x.digits.head = x.digits.head->next;
		sub.digits.count++;
	}
	while (sub.digits.head->v == 0){
		free(sub.digits.head);
		sub.digits.count--;
		sub.digits.head = sub.digits.head->next;
		if (sub.digits.head == NULL){
			break;
		}
	}
	if (sub.digits.head == NULL) {
		add(0, &sub.digits);
		sub.digits.count = 1;
	}
	sub.sign = zn;
	return sub;	
}
long_num long_numMult(long_num x, long_num y){
	int zn = x.sign * y.sign;
	long_num z;
	if (x.digits.count < y.digits.count) {
		z = x;
		x = y;
		y = z;
	}
	long_num mult;
	int k;
	long_num res;
	res.digits.head = NULL;
	add(0, &res.digits);
	res.digits.count = 1; 
	int i, j;
	node_t * p;
	for (i = 0; i < y.digits.count; i++) {
		p = x.digits.head;
		int m = 0;
		int ost = 0;
		mult.digits.head = NULL;
		mult.digits.count = 0;
		for (k = 0; k < i; k++){
			add(0, &mult.digits);
			mult.digits.count++;
		}
		for (j = 1; j <= x.digits.count; j++) {
			m = (p->v * y.digits.head->v + ost) % 10;
			ost = (p->v * y.digits.head->v + ost) / 10;
			add(m , &mult.digits);
			mult.digits.count++;
			p = p->next;
		}
		if (ost != 0) {
			add(ost, &mult.digits);
			mult.digits.count++;
		}
		mult.digits = long_numReverse(mult.digits); 
		res = long_numAdd(res, mult);
		
		res.digits = long_numReverse(res.digits);
		free(y.digits.head);
		y.digits.head = y.digits.head->next;
	}
	res.digits = long_numReverse(res.digits);
	while (res.digits.head->v == 0){
		free(res.digits.head);
		res.digits.count--;
		res.digits.head = res.digits.head->next;
		if (res.digits.head == NULL){
			break;
		}
	}
	if (res.digits.head == NULL) {
		add(0, &res.digits);
		res.digits.count = 1;
	}
	res.sign = zn;
	return res;		
}
long_num long_numDiv(long_num x, long_num y){
	long_num div;
	div.digits.head = NULL;
	div.digits.count = 1;
	add(0, &div.digits);
	if (x.digits.count <= y.digits.count) {
		if (x.digits.count < y.digits.count) {		
			if (x.sign == -1 ) {
				node_t * d = div.digits.head;
				d->v++;
				if (d->v == 10){
					d->v = 0;
					int s;
					for (s = 1; s < div.digits.count; s++){
						if (d->next->v != 9){
							d->next->v++;
							break;
						} 
						d = d->next;
					}
					if (d->v == 9){
						add(0, &div.digits);
						div.digits.count++;
						d = div.digits.head;
						for (s = 1; s < div.digits.count; s++){
							d->v = 0;
							d =d->next;
						}
						d->v = 1;
					}	
					if (d->v == 0 && d->next == NULL) {
						add(0, &div.digits);
						div.digits.count++;
						div.digits.head->next->v = 1;
						d = div.digits.head;
					}	
				}
				if (y.sign == -1) {
					div.sign = 1;
				} else {
					div.sign = -1;
				}
			}
			else {div.sign = 1;}
			return div;
		} else {
			int_list x2, y2;
			x2 = long_numReverse(x.digits);
			y2 = long_numReverse(y.digits);
			node_t * p = x2.head;
			node_t * q = y2.head;
			int w;
			for (w = 0; w < x2.count; w++) {
				if (p->v < q->v) {		
					if (x.sign == -1 ) {
						node_t * d = div.digits.head;
						d->v++;
				if (d->v == 10){
						d->v = 0;
						int s;
						for (s = 1; s < div.digits.count; s++){
							if (d->next->v != 9){
								d->next->v++;
								break;
							} 
							d = d->next;
						}
						if (d->v == 9){
							add(0, &div.digits);
							div.digits.count++;
							d = div.digits.head;
							for (s = 1; s < div.digits.count; s++){
								d->v = 0;
								d =d->next;
							}
							d->v = 1;
						}	
						if (d->v == 0 && d->next == NULL) {
							add(0, &div.digits);
							div.digits.count++;
							div.digits.head->next->v = 1;
							d = div.digits.head;
						}	
				}
				if (y.sign == -1) {
					div.sign = 1;
				} else {
					div.sign = -1;
				}
			}
					
					
					
					
					else {
						div.sign = 1;
					}
					
					
					return div;
					break; 
				}	
				p = p->next;	 	
				q = q->next;
			}
		}
	}
	int zn = x.sign * y.sign;
	int i = 1;
	int ost = 0;
	int s;
	while (i){
		node_t * p = div.digits.head;
		x = long_numSub(x, y);
		x.digits = long_numReverse(x.digits);
		p->v++;
		if (p->v == 10){
			p->v = 0;
			for (s = 1; s < div.digits.count; s++){
				p->v = 0;
				if (p->next->v != 9){
					p->next->v++;
					break;
				} 
				p = p->next;
			}
			if (p->v == 9){
				add(0, &div.digits);
				div.digits.count++;
				p = div.digits.head;
				for (s = 1; s < div.digits.count; s++){
					p = p->next;
				}
				p->v = 1;
			}	
			if (p->v == 0 && p->next == NULL) {
				add(0, &div.digits);
				div.digits.count++;
				div.digits.head->next->v = 1;
				p = div.digits.head;
			}	
		}
		if (x.digits.count < y.digits.count){
			if (x.sign == -1) {
				node_t * d = div.digits.head;
				d->v++;
				if (d->v == 10){
					d->v = 0;
					for (s = 1; s < div.digits.count; s++){
						if (d->next->v != 9){
							d->next->v++;
							break;
						} 
						d = d->next;
					}
					if (d->v == 9){
						add(0, &div.digits);
						div.digits.count++;
						d = div.digits.head;
						for (s = 1; s < div.digits.count; s++){
							d->v = 0;
							d =d->next;
						}
						d->v = 1;
					}	
					if (d->v == 0 && d->next == NULL) {
						add(0, &div.digits);
						div.digits.count++;
						div.digits.head->next->v = 1;
						d = div.digits.head;
					}	
				}
				if (y.sign == -1) {
					div.sign = 1;
				} else {
					div.sign = -1;
				}
			}
			i = 0;
		}			  
		if (x.digits.count == y.digits.count) {
			int_list x2, y2;
			x2 = long_numReverse(x.digits);
			y2 = long_numReverse(y.digits);
			node_t * p = x2.head;
			node_t * q = y2.head;
			int w;
			for (w = 1; w < x2.count; w++) {
				if (p->v > q->v) {
					break;
				}
				if (p->v < q->v) {
					i = 0;
					break;
				}	
				p = p->next;	 	
				q = q->next;
			}
			if (p->v < q->v){
				if(x.sign == -1 ){
					node_t * d = div.digits.head;
					d->v++;
					if (d->v == 10){
						d->v = 0;
						for (s = 1; s < div.digits.count; s++){
							if (d->next->v != 9){
								d->next->v++;
								break;
							} 
							d = d->next;
						}
						if (d->v == 9){
							add(0, &div.digits);
							div.digits.count++;
							d = div.digits.head;
							for (s = 1; s < div.digits.count; s++){
								d->v = 0;
								d =d->next;
							}
							d->v = 1;
						}	
						if (d->v == 0 && d->next == NULL) {
							add(0, &div.digits);
							div.digits.count++;
							div.digits.head->next->v = 1;
							d = div.digits.head;
						}	
					}
					if (y.sign == -1) {
					div.sign = 1;
					} else {
					div.sign = -1;
					}
				}
				i = 0;
			}
			if (p->v == q->v) {
				if (p->v == q->v) {
					node_t * d = div.digits.head;
					d->v++;
					if (d->v == 10){
						d->v = 0;
						for (s = 1; s < div.digits.count; s++){
							if (d->next->v != 9){
								d->next->v++;
								break;
							} 
							d = d->next;
						}
						if (d->v == 9){
							add(0, &div.digits);
							div.digits.count++;
							d = div.digits.head;
							for (s = 1; s < div.digits.count; s++){
								d->v = 0;
								d =d->next;
							}
							d->v = 1;
						}	
						if (d->v == 0 && d->next == NULL) {
							add(0, &div.digits);
							div.digits.count++;
							div.digits.head->next->v = 1;
							d = div.digits.head;
						}	
					}			
				}
				i = 0;
				break;
			}	
		 }
	}
	div.sign = zn;
	return div;
}
