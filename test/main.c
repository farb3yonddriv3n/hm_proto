#include <hmbase.h>
#include <proto.h>

struct hm_log_s *lg;

#define DUMP(m_dst, m_i, m_s)\
	int i##m_i = 0;\
	printf("dumping [%s]\n", m_s);\
	for(i##m_i = 0; i##m_i < m_i; i##m_i++) {\
		printf("%x", m_dst[i##m_i]);\
	}\
	printf("\n");

#define REPEAT\
	packet_free(p);\
	{\
		for(i = 0; i < 10; i++) {\
			parse_packet(p, buf, nbuf);\
			build_packet_test(p, buf);\
			packet_free(p);\
		}\
	}

#define build_packet_test(m_p, m_buffer)\
	char *ptrtest##m_buffer;\
	ptrtest##m_buffer = m_buffer;\
	n##m_buffer = serialize(m_p, &ptrtest##m_buffer, ptrtest##m_buffer + sizeof(m_buffer));

int main()
{
	struct packet_s *p;
	struct hm_log_s l;
	int i;

	hm_log_open(&l, NULL, LOG_DEBUG);
	lg = &l;

	// chooseoption
	{
		struct chooseoption_s *c;
		c = malloc(sizeof(*c));
		c->id = 0xffff;
		c->index = 0xffff;
		c->target = 0xffff;
		c->suboption = 0xffff;
		c->position = 0xffff;

		build_packet(p, c, P_CHOOSEOPTION, buf);
		REPEAT;
	}

	// turn timer
	{
		struct turntimer_s *c;
		c = malloc(sizeof(*c));
		c->seconds = 0xffff;
		c->turn = 0xffff;
		c->show = 0xff;

		build_packet(p, c, P_TURNTIMER, buf);
		REPEAT;
	}

	return 0;
}
