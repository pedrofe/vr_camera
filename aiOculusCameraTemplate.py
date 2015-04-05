import mtoa.ui.ae.templates as templates
class aiOculusCameraTemplate(templates.AttributeTemplate):
    def setup(self):
        self.addControl("aiMode")
        self.addControl("aiEyeSeparation")
templates.registerTranslatorUI(aiOculusCameraTemplate, "camera", "oculusCamera")
