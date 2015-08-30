import mtoa.ui.ae.templates as templates
class aiVRCameraTemplate(templates.AttributeTemplate):
    def setup(self):
        self.beginLayout("Main Attributes", collapse=False)
        self.addControl("aiMode")
        self.addControl("aiProjection")
        self.addControl("aiEyeSeparation")
        self.addControl("aiEyeToNeckDistance")
        self.endLayout()
        
        self.beginLayout("Pole Merging", collapse=False)
        self.addControl("aiTopMergeMode")
        self.addControl("aiTopMergeAngle")
        self.addControl("aiTopMergeExp")
        self.addSeparator()
        self.addControl("aiBottomMergeMode")
        self.addControl("aiBottomMergeAngle")
        self.addControl("aiBottomMergeExp")
        self.addSeparator()
        self.addControl("aiMergeShader")
        self.endLayout()

        
templates.registerTranslatorUI(aiVRCameraTemplate, "camera", "vr_camera")
