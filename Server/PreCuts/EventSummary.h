//
//  Structure "Event"
//
//  Dec. 2011 Zhe Wang
//

#ifndef _EVENTSUM_H_
#define _EVENTSUM_H_ 1

class EventSummary
{
 public:
  EventSummary()
    { Reset(); };

  ~EventSummary()
    {  };
  
 public:
  int Reset()
  {

    MuonNum = 0;
    NetMuonNum = 0;
    PlMuonNum = 0;
    AdMuonNum = 0;
    ShMuonNum = 0;
      
    return 1;
  };

 public:
  /// Event information
    int    MuonNum;
    int    NetMuonNum;
    int    PlMuonNum;
    int    AdMuonNum;
    int    ShMuonNum;

};

#endif // _EVENT_H_
