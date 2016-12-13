class flags{
	public:
		int Z;	//ZERO FLAG
		int N;	//subtraction flags
		int H;	//half-carry flag
		int C;	//Carry flag
		
		resetFlags();
		
		flags(){
			N = 0;
			Z = 0;
			H = 0;
			C = 0;
		}
};
