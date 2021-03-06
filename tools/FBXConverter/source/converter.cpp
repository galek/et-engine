#include <et/platform/platformtools.h>
#include <et/models/fbxloader.h>
#include "converter.h"

using namespace fbxc;
using namespace et;

const float invocationDelayTime = 1.0f / 3.0f;

Converter::Converter() :
	_rc(nullptr)
{
}

void Converter::setRenderContextParameters(RenderContextParameters& p)
{
	p.multisamplingQuality = MultisamplingQuality_Best;
	p.contextSize = vec2i(1024, 640);
}

void Converter::applicationDidLoad(RenderContext* rc)
{
	_rc = rc;
	_rc->renderState().setDepthTest(true);

	_gestures.pointerPressed.connect(this, &Converter::onPointerPressed);
	_gestures.pointerMoved.connect(this, &Converter::onPointerMoved);
	_gestures.pointerReleased.connect(this, &Converter::onPointerReleased);
	_gestures.scroll.connect(this, &Converter::onScroll);
	_gestures.zoom.connect(this, &Converter::onZoom);
	_gestures.drag.connect(this, &Converter::onDrag);

	_gui = new gui::Gui(rc);
	_mainLayout = IntrusivePtr<MainLayout>(new MainLayout());
	_gui->pushLayout(_mainLayout, 0, 0.0f);
	_mainFont = gui::Font(rc, "ui/fonts/main.font", _texCache);

	Texture uiTexture = rc->textureFactory().loadTexture("gui/keyboard.png", _texCache);

	gui::ContentOffset defOffset(8.0f);
	gui::Image imgNormalState(uiTexture, gui::ImageDescriptor(vec2(128.0f, 0.0f), vec2(32.0f), defOffset));
	gui::Image imgHoverState(uiTexture, gui::ImageDescriptor(vec2(160.0f, 0.0f), vec2(32.0f), defOffset));
	gui::Image imgPressedState(uiTexture, gui::ImageDescriptor(vec2(192.0f, 0.0f), vec2(32.0f), defOffset));
	gui::Image imgSelectedNormalState(uiTexture, gui::ImageDescriptor(vec2(128.0f, 32.0f), vec2(32.0f), defOffset));
	gui::Image imgSelectedHoverState(uiTexture, gui::ImageDescriptor(vec2(160.0f, 32.0f), vec2(32.0f), defOffset));
	gui::Image imgSelectedPressedState(uiTexture, gui::ImageDescriptor(vec2(192.0f, 32.0f), vec2(32.0f), defOffset));

	gui::Button::Pointer btnOpen(new gui::Button("Open", _mainFont, _mainLayout.ptr()));
	btnOpen->setBackgroundForState(imgNormalState, gui::State_Default);
	btnOpen->setBackgroundForState(imgHoverState, gui::State_Hovered);
	btnOpen->setBackgroundForState(imgPressedState, gui::State_Pressed);
	btnOpen->clicked.connect(this, &Converter::onBtnOpenClick);

	gui::Button::Pointer btnSaveBin(new gui::Button("Save (etm)", _mainFont, _mainLayout.ptr()));
	btnSaveBin->tag = 1;
	btnSaveBin->setBackgroundForState(imgNormalState, gui::State_Default);
	btnSaveBin->setBackgroundForState(imgHoverState, gui::State_Hovered);
	btnSaveBin->setBackgroundForState(imgPressedState, gui::State_Pressed);
	btnSaveBin->setPosition(btnOpen->size().x, 0.0f);
	btnSaveBin->clicked.connect(this, &Converter::onBtnSaveClick);

	gui::Button::Pointer btnSaveHRM(new gui::Button("Save (etm+xml)", _mainFont, _mainLayout.ptr()));
	btnSaveHRM->tag = 2;
	btnSaveHRM->setBackgroundForState(imgNormalState, gui::State_Default);
	btnSaveHRM->setBackgroundForState(imgHoverState, gui::State_Hovered);
	btnSaveHRM->setBackgroundForState(imgPressedState, gui::State_Pressed);
	btnSaveHRM->setPosition(btnOpen->size().x + btnSaveBin->size().x, 0.0f);
	btnSaveHRM->clicked.connect(this, &Converter::onBtnSaveClick);

	_btnDrawNormalMeshes = gui::Button::Pointer(new gui::Button("Normal", _mainFont, _mainLayout.ptr()));
	_btnDrawNormalMeshes->setBackgroundForState(imgNormalState, gui::State_Default);
	_btnDrawNormalMeshes->setBackgroundForState(imgHoverState, gui::State_Hovered);
	_btnDrawNormalMeshes->setBackgroundForState(imgPressedState, gui::State_Pressed);
	_btnDrawNormalMeshes->setBackgroundForState(imgSelectedNormalState, gui::State_Selected);
	_btnDrawNormalMeshes->setBackgroundForState(imgSelectedHoverState, gui::State_SelectedHovered);
	_btnDrawNormalMeshes->setBackgroundForState(imgSelectedPressedState, gui::State_SelectedPressed);
	_btnDrawNormalMeshes->setPivotPoint(vec2(1.0f));
	_btnDrawNormalMeshes->setPosition(_rc->size());
	_btnDrawNormalMeshes->setType(gui::Button::Type_CheckButton);
	_btnDrawNormalMeshes->setSelected(true);

	_btnDrawSupportMeshes = gui::Button::Pointer(new gui::Button("Support", _mainFont, _mainLayout.ptr()));
	_btnDrawSupportMeshes->setBackgroundForState(imgNormalState, gui::State_Default);
	_btnDrawSupportMeshes->setBackgroundForState(imgHoverState, gui::State_Hovered);
	_btnDrawSupportMeshes->setBackgroundForState(imgPressedState, gui::State_Pressed);
	_btnDrawSupportMeshes->setBackgroundForState(imgSelectedNormalState, gui::State_Selected);
	_btnDrawSupportMeshes->setBackgroundForState(imgSelectedHoverState, gui::State_SelectedHovered);
	_btnDrawSupportMeshes->setBackgroundForState(imgSelectedPressedState, gui::State_SelectedPressed);
	_btnDrawSupportMeshes->setPivotPoint(vec2(1.0f, 0.0f));
	_btnDrawSupportMeshes->setPosition(_btnDrawNormalMeshes->origin());
	_btnDrawSupportMeshes->setType(gui::Button::Type_CheckButton);
	_btnDrawSupportMeshes->setSelected(true);

	_btnWireframe = gui::Button::Pointer(new gui::Button("Wireframe", _mainFont, _mainLayout.ptr()));
	_btnWireframe->setBackgroundForState(imgNormalState, gui::State_Default);
	_btnWireframe->setBackgroundForState(imgHoverState, gui::State_Hovered);
	_btnWireframe->setBackgroundForState(imgPressedState, gui::State_Pressed);
	_btnWireframe->setBackgroundForState(imgSelectedNormalState, gui::State_Selected);
	_btnWireframe->setBackgroundForState(imgSelectedHoverState, gui::State_SelectedHovered);
	_btnWireframe->setBackgroundForState(imgSelectedPressedState, gui::State_SelectedPressed);
	_btnWireframe->setPivotPoint(vec2(1.0f, 0.0f));
	_btnWireframe->setPosition(_btnDrawSupportMeshes->origin());
	_btnWireframe->setType(gui::Button::Type_CheckButton);
	_btnWireframe->setSelected(false);
	
	_vDistance.setTargetValue(300.0f);
	_vDistance.updated.connect(this, &Converter::onCameraUpdated);
	_vDistance.finishInterpolation();
	_vDistance.run();

	_vAngle.setTargetValue(vec2(QUARTER_PI));
	_vAngle.updated.connect(this, &Converter::onCameraUpdated);
	_vAngle.finishInterpolation();
	_vAngle.run();

	_labStatus = gui::Label::Pointer(new gui::Label("Status", _mainFont, _mainLayout.ptr()));
	_labStatus->setPivotPoint(vec2(0.0f, 1.0f));
	_labStatus->setPosition(0.0f, _rc->size().y);
	_labStatus->setText("Ready.");

	_camera.perspectiveProjection(QUARTER_PI, rc->size().aspect(), 1.0f, 2048.0f);
	_camera.lookAt(fromSpherical(_vAngle.value().x, _vAngle.value().y) * _vDistance.value());

	ObjectsCache localCache;
	
	_defaultProgram = rc->programFactory().loadProgram("shaders/default.program", localCache);
	_defaultProgram->setPrimaryLightPosition(500.0f * vec3(0.0f, 1.0f, 0.0f));
	_defaultProgram->setUniform("diffuseMap", 0);
	_defaultProgram->setUniform("specularMap", 1);
	_defaultProgram->setUniform("normalMap", 2);

	rc->renderState().setClearColor(vec4(0.25f));
	rc->renderState().setDepthTest(true);
	rc->renderState().setDepthMask(true);
	rc->renderState().setBlend(true, BlendState_Default);
	
	const std::string& lp = application().launchParameter(1);
	if (fileExists(lp))
	{
		Invocation1 i;
		i.setTarget(this, &Converter::performLoading, lp);
		i.invokeInMainRunLoop(invocationDelayTime);
	}
}

void Converter::renderMeshList(RenderContext* rc, const s3d::Element::List& meshes)
{
	for (auto i = meshes.begin(), e = meshes.end(); i != e; ++i)
	{
		s3d::Mesh::Pointer mesh = *i;
		if (mesh->active())
		{
			const s3d::Material::Pointer& m = mesh->material();
			
			_defaultProgram->setUniform("ambientColor", m->getVector(MaterialParameter_AmbientColor));
			_defaultProgram->setUniform("diffuseColor", m->getVector(MaterialParameter_DiffuseColor));
			_defaultProgram->setUniform("specularColor", m->getVector(MaterialParameter_SpecularColor));
			_defaultProgram->setUniform("roughness", m->getFloat(MaterialParameter_Roughness));
			_defaultProgram->setUniform("mTransform", mesh->finalTransform());
			
			rc->renderState().bindTexture(0, mesh->material()->getTexture(MaterialParameter_DiffuseMap));
			rc->renderState().bindTexture(1, mesh->material()->getTexture(MaterialParameter_SpecularMap));
			rc->renderState().bindTexture(2, mesh->material()->getTexture(MaterialParameter_NormalMap));
			
			rc->renderState().bindVertexArray(mesh->vertexArrayObject());
			rc->renderer()->drawElements(mesh->indexBuffer(), mesh->startIndex(), mesh->numIndexes());
		}
	}
}

void Converter::performSceneRendering()
{
	_rc->renderState().bindProgram(_defaultProgram);
	_defaultProgram->setCameraProperties(_camera);

	if (_btnDrawNormalMeshes->selected())
		renderMeshList(_rc, _scene.childrenOfType(s3d::ElementType_Mesh));

	if (_btnDrawSupportMeshes->selected())
		renderMeshList(_rc, _scene.childrenOfType(s3d::ElementType_SupportMesh));
}

void Converter::render(RenderContext* rc)
{
	rc->renderer()->clear();

	rc->renderState().setWireframeRendering(_btnWireframe->selected());
	performSceneRendering();
	rc->renderState().setWireframeRendering(false);
	
	_gui->render(rc);
}

void Converter::onPointerPressed(et::PointerInputInfo p)
{
	_vDistance.cancelInterpolation();
	_vAngle.cancelInterpolation();
	
	_gui->pointerPressed(p);
}

void Converter::onPointerMoved(et::PointerInputInfo p)
{
	_gui->pointerMoved(p);
}

void Converter::onPointerReleased(et::PointerInputInfo p)
{
	_gui->pointerReleased(p);
}

void Converter::onZoom(float z)
{
	_vDistance.addTargetValue(z);
}

void Converter::onDrag(et::vec2 v, et::PointerType)
{
	_vAngle.addTargetValue(0.25f * vec2(-v.y, v.x));
}

void Converter::onScroll(et::vec2 s, et::PointerOrigin o)
{
	if (o == PointerOrigin_Mouse)
		onZoom(s.y);
	else if (o == PointerOrigin_Trackpad)
		onZoom(100.0f * s.y);
}

void Converter::onBtnOpenClick(et::gui::Button*)
{
	StringList types;
	types.push_back("fbx");
	types.push_back("etm");
	std::string fileName = selectFile(types, SelectFileMode_Open, std::string());
	
	if (fileExists(fileName))
	{
		_scene.clear();
		
		Invocation1 i;
		i.setTarget(this, &Converter::performLoading, fileName);
		i.invokeInMainRunLoop(invocationDelayTime);
		
		_labStatus->setText("Loading...");
	}
	else
	{
		_labStatus->setText("No file selected or unable to locate selected file");
	}
}

void Converter::onBtnSaveClick(et::gui::Button* b)
{
	std::string fileName = selectFile(StringList(), SelectFileMode_Save, _scene.name());
	
	Invocation1 i;

	i.setTarget(this, (b->tag == 1 ? &Converter::performBinarySaving :
		&Converter::performBinaryWithReadableMaterialsSaving), fileName);
	
	i.invokeInMainRunLoop(invocationDelayTime);
	
	_labStatus->setText("Saving...");
}

void Converter::performLoading(std::string path)
{
	lowercase(path);
	size_t value = path.find_last_of(".etm");
	size_t len = path.length();

	if (value == len-1)
	{
		_scene.deserialize(path, _rc, _texCache, 0);
	}
	else
	{
		FBXLoader loader(path);

		s3d::ElementContainer::Pointer loadedScene = loader.load(_rc, _texCache);
		
		if (loadedScene.valid())
			loadedScene->setParent(&_scene);
	}
	
	auto nodesWithAnimation = _scene.childrenHavingFlag(s3d::Flag_HasAnimations);
	
	for (auto& i : nodesWithAnimation)
		i->animate();
	
	_labStatus->setText("Completed.");
}

void Converter::performBinarySaving(std::string path)
{
	if (path.find_last_of(".etm") != path.length() - 1)
		path += ".etm";

	_scene.serialize(path, s3d::StorageFormat_Binary);
	_labStatus->setText("Completed.");
}

void Converter::performBinaryWithReadableMaterialsSaving(std::string path)
{
	if (path.find_last_of(".etm") != path.length() - 1)
		path += ".etm";

	_scene.serialize(path, s3d::StorageFormat_HumanReadableMaterials);
	_labStatus->setText("Completed.");
}

void Converter::onCameraUpdated()
{
	_camera.lookAt(fromSpherical(_vAngle.value().x, _vAngle.value().y) * _vDistance.value());
}

et::ApplicationIdentifier Converter::applicationIdentifier() const
	{ return ApplicationIdentifier("com.cheetek.fbxconverter", "Cheetek", "FBXConverter"); }

et::IApplicationDelegate* et::Application::initApplicationDelegate()
	{ return new fbxc::Converter(); }
