//
//  Structure "Event"
//
//  Dec. 2011 Zhe Wang
//

#ifndef _EVENT_H_
#define _EVENT_H_ 1

#define MaxFold 200

class Event
{
 public:
  Event()
    { Reset(); };

  ~Event()
    {  };
  
 public:
  int Reset()
  {
    Run = -1;
    Det = -1;
      Fold = 0;
    
      TrigSec = -1;
      TrigNano = -1;
      TrigNo = -1;
      E = -1;
      X = -1;
      Y = -1;
      Z = -1;

    T2PrevPlMu = -1;
    T2PrevAdMu = -1;
    T2PrevShMu = -1;
      
      FullTime = -1;
      LiveTime = -1;
      TimeGap = -1;
      
      AdMu   = 0;
      ShMu   = 0;
      WpMu   = 0;
      NetMu  = 0;
    return 1;
  };

 public:
  /// Event information
  int    Run;
  int    Det;
    int    Fold;

  double T2PrevPlMu;
  double T2PrevAdMu;
  double T2PrevShMu;

  int    TrigSec;
  int    TrigNano;
    int TrigNo;

  double E;
  double X;
  double Y;
  double Z;

    double LiveTime;
    double FullTime;
    double TimeGap;
    
    int AdMu;
    int ShMu;
    int WpMu;
    int NetMu;
};

#endif // _EVENT_H_
