#include "ConformalMesherLauncherTest.h"

TEST_F(ConformalMesherLauncherTest, Structured){
    const string project = "B2";
    CVecR3 step(1,1,1);
    // >>>>>>>>>>>>>>>>>>> runs ugrMesher <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    ProjectFile ugrMesher("/usr/local/bin/ugrMesher");
    string args = "-auto 1 1 1 -s " + stlFolder_ + "B2.stl -o B2 --structured";
    ugrMesher.exec(args);
    // >>>>>>>>>>>>>>>>>>> runs meshConf <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    SmbData* smb = parseFromSTL(project);
    // Prepares data for mesher.
    smb->pMGroup = new GroupPhysicalModels<>();
    MatId pecId(1);
    smb->pMGroup->add(new PMPEC(pecId, "PEC"));
    smb->mesh->castTo<MeshUnstructured>()->setMatId(pecId);
    BoxR3 bound = smb->mesh->castTo<MeshUnstructured>()->getBoundingBox();
    smb->grid = new Grid3(bound, step);
    smb->mesherOptions = new OptionsMesher();
    smb->emSources = new GroupEMSources<>();
    smb->outputRequests = new GroupOutRqs<>();
    // Launches adapter.
    SmbData* nfde = new SmbData();
    AdapterFDTD(*smb).convert(*nfde);
    {
        ExporterVTK outVTKSmb(smb, stlFolder_ + project + "_smb");
        ExporterVTK outVTKNFDE(nfde, stlFolder_ + project + "_nfde");
        ExporterNFDE outNFDE(*nfde);
    }
    delete smb;
    //
    ProjectFile cmshBase;
    ProjectFile cmshNew;
    compare(cmshBase, cmshNew);
}

//INSTANTIATE_TEST_CASE_P(
//        stls, ConformalMesherLauncherTest, ::testing::Values(
//                "B2",
//                "ev55",
//                "scrub2"
//        ));

