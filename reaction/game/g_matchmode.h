void		MM_RunFrame( void );
void		MM_Captain_f(gentity_t *ent );
void		MM_Sub_f( gentity_t *ent);
void		MM_Ready_f(gentity_t *ent);
void		MM_ClearScores( void );

// aasimon: Declarations for Ref system 
qboolean	Ref_Exists( void );
qboolean	Ref_Auth( gentity_t *);  // No need to return a boolean in this context
void		Ref_Command ( gentity_t * );
void		Ref_Resign ( gentity_t * );
