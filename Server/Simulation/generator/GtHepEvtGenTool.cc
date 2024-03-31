#include "GtHepEvtGenTool.h"
#include "HepEvt2HepMC.h"

#include "Event/HepMCEvent.h"
#include "HepMC/GenEvent.h"

#include <cstdio>



GtHepEvtGenTool::GtHepEvtGenTool(const std::string& type,
                                 const std::string& name,
                                 const IInterface* parent)
    : GaudiTool(type,name,parent)
    , m_parser(0)
{
    declareInterface<IHepMCEventMutator>(this);

    declareProperty("HepEvtDataSource",m_source = "","Source of HEPEvt data");
}

GtHepEvtGenTool::~GtHepEvtGenTool() {}

StatusCode GtHepEvtGenTool::initialize()
{
    info() << "GtHepEvtGenTool::initialize()" << endreq;

    if (this->GaudiTool::initialize().isFailure()) {
        fatal() << "Parent Tool class initialization failed" << endreq;
        return StatusCode::FAILURE;
    }

    m_source = "/data5/wangzhe/zlab/Production/muonEvt.txt";

    return StatusCode::SUCCESS;
}

StatusCode GtHepEvtGenTool::finalize()
{
    if (m_parser) delete m_parser; m_parser = 0;

    return this->GaudiTool::finalize();
}

StatusCode GtHepEvtGenTool::mutate(HepMC::GenEvent& event)
{
    if (!m_parser) {
        if ("" == m_source) {
            fatal() << "No HEPEvt source string given." << endreq;
            return StatusCode::FAILURE;
        }
        m_parser = new HepEvt2HepMC;
        if (m_parser->fill(m_source.c_str()).isFailure()) {
            fatal () << "Failed to fill primary vertices using \""
                     << m_source << "\"" << endreq;
            return StatusCode::FAILURE;
        }
        info () << "Filled HEPEvt cache with " << m_parser->cacheSize()
                << " events" << endreq;
    }
    else {
        if( m_parser->cacheSize()>0 )  {
	    debug () << "Reusing cache with " << m_parser->cacheSize()
		    << " events left" << endreq;
	} else {
	    warning() << "WARNING: Reuse input source! Recommend more input lines!"<< endreq;
	    if (m_parser->fill(m_source.c_str()).isFailure()) {
	      fatal () << "Failed to fill primary vertices using \""
		       << m_source << "\"" << endreq;
	      return StatusCode::FAILURE;
	    }
	    info () << "Filled HEPEvt cache with " << m_parser->cacheSize()
		    << " events" << endreq;
	}
    }

    HepMC::GenEvent* new_event=0;
    if (m_parser->generate(new_event).isFailure()) {
        fatal() << "Failed to generate new event" << endreq;
        if (new_event) delete new_event;
        return StatusCode::FAILURE;
    }
    event = *new_event;
    delete new_event;

    HepMC::FourVector pos = event.signal_process_vertex()->position();
    debug() << "HepEvt at (" <<pos.x() << "," << pos.y() << "," << pos.z() << ")" << endreq;

    return StatusCode::SUCCESS;
}
