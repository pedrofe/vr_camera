import mtoa.ui.ae.templates as templates
class aiOculusCameraTemplate(templates.AttributeTemplate):
    def setup(self):
        self.beginLayout("Main Attributes", collapse=False)
        self.addControl("aiMode")
        self.addControl("aiProjection")
        self.addControl("aiEyeSeparation")
        self.endLayout()
        
        self.beginLayout("Pole Merging", collapse=False)
        self.addControl("aiTopMergeMode")
        self.addControl("aiTopMergeAngle")
        self.addControl("aiTopMergeExp")
        self.addSeparator()
        self.addControl("aiBottomMergeMode")
        self.addControl("aiBottomMergeAngle")
        self.addControl("aiBottomMergeExp")
        self.endLayout()
        
templates.registerTranslatorUI(aiOculusCameraTemplate, "camera", "oculusCamera")
