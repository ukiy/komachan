//�悭����p��
//W: ��, B: ��, �`�F�X�R���ł���C���𔒁C�������Ƃ���
//sq: square�̗��Ń}�X��\��
//ply: �`�F�X�Ȃǂŗp������,�^�[���Ɏ����T�O
//��l���̍s����1�v���C�ƌĂԁD��l��ply�����킹��1�^�[���Ƃ���ꍇ������D
//��: �`�F�X�ɂ�����20�^�[����,��20, ��20��40�v���C�Ɠ�����
//bb: �r�b�g�{�[�h
//move: �w����
//hand: ������


#define RECORD_SIZE        256
#define SIZE_LEGALMOVES    256

//�Q�[���̏�Ԃ������\����
typedef struct tree tree_t;
struct tree
{
  unsigned int BBs[32]; //�o���̔Ֆʂ̏��
  unsigned int whand; //���Ԃ̎�����
  unsigned int bhand; //���Ԃ̎�����
  int sq_wking; //���̋ʂ̈ʒu
  int sq_bking; //���̋ʂ̈ʒu
  char turn; //���݂̎��
  short n_ply; //���݂̎萔
};

//�w����̗����ЂƂ��������\����
typedef struct
{
  unsigned int move;
} hist_t;

//game�ɁC�Q�[���̑S��Ԃ��i�[���Ă����B
//history�́C�w����̔z��B����܂ł̎��o�^����?
extern tree_t game;
extern hist_t history[ RECORD_SIZE ];
//2�i����\������.binary
enum { b0000, b0001, b0010, b0011, b0100, b0101, b0110, b0111,
       b1000, b1001, b1010, b1011, b1100, b1101, b1110, b1111,
       b1_1111 = 31  };

// ��̏�Ԃ�\���ԍ��D
// 4�Ԗڂ̃r�b�g�𗧂Ă鎖�Ő��鎖���ł���D
// pro_pawn == pawn | m_promote
// b(��)�̋��5�Ԗڂ̃r�b�g�������Ă���D
enum{
  m_promote    =  b1000,

  pawn         =  1,
  silver       =  4,
  gold         =  5,
  bishop       =  6,
  rook         =  7,
  king         =  8,
  pro_pawn     =  9,
  pro_silver   = 12,
  horse        = 14,
  dragon       = 15,

  w_pawn       =  1,
  w_silver     =  4,
  w_gold       =  5,
  w_bishop     =  6,
  w_rook       =  7,
  w_king       =  8,
  w_pro_pawn   =  9,
  w_pro_silver = 12,
  w_horse      = 14,
  w_dragon     = 15,

  b_pawn       = 17,
  b_silver     = 20,
  b_gold       = 21,
  b_bishop     = 22,
  b_rook       = 23,
  b_king       = 24,
  b_pro_pawn   = 25,
  b_pro_silver = 28,
  b_horse      = 30,
  b_dragon     = 31,

  bbs_size
};
// �w������̎擾�Ɏg���}�W�b�N�i���o�[
// �w����̕ϐ��ɁC�}�X�N�������ė~���������擾����
// move & b1_1111�Ƃ����g�����ŁC�ŉE��5�r�b�g���������o�����Ƃ��ł���
// ��: ..0000 1111 1011 1101 & 1 1111 => ..0000 0000 0001 1101
// �ŉE����5�r�b�g����̎�ށC����5�r�b�g�������O�̈ʒu�c�ƕ\������
// �ϐ����Ƃɍ��V�t�g�Ń}�X�N��������ʒu�����炵�Ă���D
enum{
  move_drop          =  25, //��ł��������ԍ�
  move_mask_type     = (b1_1111 << 0 ),
  move_mask_from     = (b1_1111 << 5 ),
  move_mask_to       = (b1_1111 << 10),
  move_mask_promote  = (b0001   << 15),
  move_mask_capture  = (b0001   << 16),
  move_mask_captured = (b1_1111   << 17),
};
//�֗��}�X�N�B�~�����Ƃ����&���Z���邱�ƂŕK�v�Ȓl����邱�Ƃ��ł���
enum{
  bb_mask            =  0x01ffffff,//�Ֆʂ̌v�Z�Ώۂ�25bit���}�X�N����
  mask_magic         =  0x0000003f,//�}�W�b�N�i���o�[�v�Z�p��6bit���}�X�N
  mask_type          =  b1111,//���p����
  mask_type_c        =  b1_1111,//���p����
  mask_nopro         =  b0111,//��̎�ނɂ���3bit���}�X�N����ΐ���O�̋�킪�Ƃ��
  mask_piece_color   = (b0001 << 4),//��̎�Ԃ�5bit�ڂ��}�X�N����΂Ƃ��
  white              =  0,
  black              =  1,
  myturn_not_set     =  -1,
  no_piece           =  -1
};

//�r�b�g�{�[�h�ւ̃A�N�Z�X��֗��ɂ��邽�߂̃}�N��
//���Ƃ���BB_W_PAWN�Ƃ���ƁC���Ԃ̕��̏�Ԃ�\���r�b�g�{�[�h�ϐ�������
#define BB_ALL           (game.BBs)
#define BB_N(n)          (game.BBs[n])

#define BB_W_PAWN        (game.BBs[w_pawn])
#define BB_W_SILVER      (game.BBs[w_silver])
#define BB_W_GOLD        (game.BBs[w_gold])
#define BB_W_BISHOP      (game.BBs[w_bishop])
#define BB_W_ROOK        (game.BBs[w_rook])
#define BB_W_PRO_PAWN    (game.BBs[w_pro_pawn])
#define BB_W_PRO_SILVER  (game.BBs[w_pro_silver])
#define BB_W_HORSE       (game.BBs[w_horse])
#define BB_W_DRAGON      (game.BBs[w_dragon])
#define BB_W_KING        (game.BBs[w_king])
#define SQ_W_KING        (game.sq_wking)

#define BB_B_PAWN        (game.BBs[b_pawn])
#define BB_B_SILVER      (game.BBs[b_silver])
#define BB_B_GOLD        (game.BBs[b_gold])
#define BB_B_BISHOP      (game.BBs[b_bishop])
#define BB_B_ROOK        (game.BBs[b_rook])
#define BB_B_PRO_PAWN    (game.BBs[b_pro_pawn])
#define BB_B_PRO_SILVER  (game.BBs[b_pro_silver])
#define BB_B_HORSE       (game.BBs[b_horse])
#define BB_B_DRAGON      (game.BBs[b_dragon])
#define BB_B_KING        (game.BBs[b_king])
#define SQ_B_KING        (game.sq_bking)

#define W_HAND_A          (game.whand)
#define B_HAND_A          (game.bhand)
#define IsHand_W(piece)   (W_HAND_A & ( b0011 << ((piece)*2) ))
#define IsHand_B(piece)   (B_HAND_A & ( b0011 << ((piece)*2) ))
#define W_HAND(piece)     (int)((W_HAND_A >> ((piece)*2)) & b0011)
#define B_HAND(piece)     (int)((B_HAND_A >> ((piece)*2)) & b0011)
#define HAND_ADD(piece)   (1 << ((piece)*2))
/* hand
  ........ ........ ....xx.. pawn
  ........ ......xx ........ silver
  ........ ....xx.. ........ gold
  ........ ..xx.... ........ bishop
  ........ xx...... ........ rook
  */

#define TURN             (game.turn)
#define N_PLY            (game.n_ply)
//���[�e�B���e�B�֐�
//x�Ԗڂ𗧂Ă��r�b�g��p�ӂ���
#define Bit(x)           ( 1 << x )
//x, y�ɂ����W�n����ϊ����C�Ֆʂ̓Y�����������D
#define XY2INDEX(x,y)    ( (5-x) + (y-1)*5 )
//
#define INVERSE(x)       ( 24 - x )

//�n�߂Ƀr�b�g�������Ă���ʒu���擾����
#define FIRSTONE(bb)   (31 - __builtin_clz( bb )) /* ret -1: bb = 0 */

/* move 
  ........ ........ ...xxxxx piece to move
  ........ ......xx xxx..... starting square ( 25-> drop )
  ........ .xxxxx.. ........ destination
  ........ x....... ........ promote or not
  .......x ........ ........ capture something
  xxxxxxx. ........ ........ captured piece  (0 -> unknown)
 */

//�w���肩������擾����}�N��
//��L�̃}�X�N��p���Ď擾���Ă���
//��̎�ށC�ړ��O�E��C���������ۂ��C�����������ۂ��C�������̎��
//���������ۂ�?�����Ă��邩�ۂ��H�͗v����
#define MOVE_TYPE(move)           ( (move & move_mask_type)         )
#define MOVE_FROM(move)           ( (move & move_mask_from)    >> 5 )
#define MOVE_TO(move)             ( (move & move_mask_to)      >> 10)
#define MOVE_PROMOTE(move)        ( (move & move_mask_promote) >> 15)
#define MOVE_CAPTURE(move)        ( (move & move_mask_capture) >> 16)
#define MOVE_CAPTURED_TYPE(move)  ( (move & move_mask_captured)>> 17)
//NULL�̎w�����\��
#define MOVE_NULL                 0

//�ߊl������̎�ނ��i�[����ʒu�ɑΉ������邽�߂̃r�b�g�V�t�g
#define CAPTURED_2_MOVE(cap)      ( cap << 17 )

//�r�b�g�{�[�h�������ɁC���ꂼ��Y�����錅�ɂ��낦��悤�Ƀr�b�g�V�t�g����. 
//������Ȃ��ꍇ�̎w�����\���r�b�g�{�[�h�𐶐�����
#define MOVE(v1, v2, v3, v4, v5) ( (v1) + (v2 << 5) + (v3 << 10) +\
                                   (v4 << 15) + (v5 << 16) + (0 << 17) )
//������ꍇ�̎w�����\���r�b�g��𐶐�����D
#define MOVE_C(v1, v2, v3, v4, v5, v6)\
                                   ( (v1) + (v2 << 5) + (v3 << 10) +\
                                   (v4 << 15) + (v5 << 16) + (v6 << 17) )

//�w����𔽉f������}�N��
//���݂̎�Ԃ̃v���C����make_move���Ăяo���D
#define MAKE_MOVE(move)       TURN ? make_move_b( move ) : make_move_w( move );
#define UNMAKE_MOVE           TURN ? unmake_move_w() : unmake_move_b();
//��Ԃ����ւ���Dblack^black�Ȃ�white�ɁBwhite^black�Ȃ�black�ɂȂ�D
#define FLIP_TURN             TURN ^= black;

//calc_occupied_sq()�ɂ�bb_mask������
//make_move_w�ɂāC��̈ړ���ɂ�
extern unsigned int nOccupiedW;
extern unsigned int nOccupiedB;
extern unsigned int Occupied0;

//starting_initialize()�ɂ�FILE_READ����Ă���D
extern unsigned int Attack_WPawn[32];
extern unsigned int Attack_WSilver[32];
extern unsigned int Attack_WGold[32];
extern unsigned int Attack_BPawn[32];
extern unsigned int Attack_BSilver[32];
extern unsigned int Attack_BGold[32];
extern unsigned int Attack_King[32];
extern unsigned int Attack_Rook[32][64];
extern unsigned int Attack_Rook_magic[32];
extern unsigned int Attack_Rook_mask[32];
extern const    int Attack_Rook_shift[32];
extern unsigned int Attack_Bishop[32][64];
extern unsigned int Attack_Bishop_magic[32];
extern unsigned int Attack_Bishop_mask[32];
extern const    int Attack_Bishop_shift[32];
extern unsigned int Pin_Rook[32][32][64][2];
extern unsigned int Pin_Bishop[32][32][64][2];
extern unsigned int DoublePawn[32];

//�������烉�C�u�����̗p�ӂ���֐��Q

//�Q�[����Ԃ̕ύX
int starting_initialize(); //�������̏�����
void clear_game(); //�ՖʁE��ԁE�������������ԂɃ��Z�b�g
void make_move_w( unsigned int move );
void make_move_b( unsigned int move );
void unmake_move_w( );
void unmake_move_b( );
//�w���萶���Ɋւ��֐�
int gen_legalmoves( unsigned legalmoves[] );
int gen_evasion_w( unsigned int moves[], int count, int nAttacks,
                   unsigned int attack_pieces, unsigned int pin[] );
int gen_evasion_b( unsigned int moves[], int count, int nAttacks,
                   unsigned int attack_pieces, unsigned int pin[] );
int gen_cap_w( unsigned int moves[], int count, unsigned int pin[] );
int gen_cap_b( unsigned int moves[], int count, unsigned int pin[] );
int gen_nocap_w( unsigned int moves[], int count, unsigned int pin[] );
int gen_nocap_b( unsigned int moves[], int count, unsigned int pin[] );
int gen_drop_w( unsigned int moves[], int count );
int gen_drop_b( unsigned int moves[], int count );
int gen_attacks_to_w( unsigned int moves[], int count, int sq, int cap, unsigned int pin[] );
int gen_attacks_to_b( unsigned int moves[], int count, int sq, int cap, unsigned int pin[] );
int mate_by_dropping_pawn_w( int sq );
int mate_by_dropping_pawn_b( int sq );
//����������Ă���ʒu�̐���Ԃ�
int attacks_to_w( int sq, unsigned int *attack_pieces );
int attacks_to_b( int sq, unsigned int *attack_pieces );
void pinInfo_w( unsigned int pin[32] );
void pinInfo_b( unsigned int pin[32] );
//�n�߂Ƀr�b�g�������Ă���ʒu��Ԃ�.FIRSTONE�}�N���Ƃ̈Ⴂ�́H
int FirstOne( int bb );
//�}�X�ɑ��݂����
int get_piece_on_sq_w( int sq );
int get_piece_on_sq_b( int sq );
int get_piece_on_sq( int sq );
//��̂���ʒu�S�Ă��v�Z���ď�������
void calc_occupied_sq();
int popuCount( int piece );
//���݂̎��(TURN)��black��white�ŕԂ�
int get_turn();
//N_PLY��Ԃ�
int get_nply();
