#include "CommandDictionary.h"

#include "CmdBeginDraw.h"
#include "CmdDrawPixel.h"
#include "CmdEnableDepth.h"
#include "CmdEndDraw.h"
#include "CmdPopMatrix.h"
#include "CmdPushRotationX.h"
#include "CmdPushRotationY.h"
#include "CmdPushRotationZ.h"
#include "CmdPushScaling.h"
#include "CmdPushTranslation.h"
#include "CmdSetCameraDirection.h"
#include "CmdSetCameraFarPlane.h"
#include "CmdSetCameraFov.h"
#include "CmdSetCameraNearPlane.h" 
#include "CmdSetCameraPosition.h"
#include "CmdSetClipping.h"
#include "CmdSetColor.h"
#include "CmdSetCullMode.h"
#include "CmdSetFillMode.h"
#include "CmdSetResolution.h"
#include "CmdSetViewport.h"
#include "CmdShowViewport.h"
#include "CmdVarBool.h"
#include "CmdVarFloat.h"
#include "CmdVertex.h"
#include "CmdPopMatrix.h"

CommandDictionary* CommandDictionary::Get()
{
	static CommandDictionary sInstance;
	return &sInstance;
}

CommandDictionary::CommandDictionary()
{
	// Initialize dictionary

	// Setting commands
	RegisterCommand<CmdSetResolution>();

	// Variable commands
	RegisterCommand<CmdVarBool>();
	RegisterCommand<CmdVarFloat>();

	// Rasterization commands
	RegisterCommand<CmdBeginDraw>();
	RegisterCommand<CmdDrawPixel>();
	RegisterCommand<CmdEndDraw>();
	RegisterCommand<CmdSetColor>();
	RegisterCommand<CmdSetCullMode>();
	RegisterCommand<CmdSetFillMode>();
	RegisterCommand<CmdVertex>();

	// Viewport commands
	RegisterCommand<CmdSetViewport>();
	RegisterCommand<CmdShowViewport>();
	RegisterCommand<CmdSetClipping>();

	// Matrix Stack commands
	RegisterCommand<CmdPopMatrix>();
	RegisterCommand<CmdPushRotationX>();
	RegisterCommand<CmdPushRotationY>();
	RegisterCommand<CmdPushRotationZ>();
	RegisterCommand<CmdPushScaling>();
	RegisterCommand<CmdPushTranslation>();

	// Camera commands
	RegisterCommand<CmdSetCameraDirection>();
	RegisterCommand<CmdSetCameraFarPlane>();
	RegisterCommand<CmdSetCameraFov>();
	RegisterCommand<CmdSetCameraNearPlane>();
	RegisterCommand<CmdSetCameraPosition>();
	RegisterCommand<CmdEnableDepth>();

	// Set Color Command
}

TextEditor::LanguageDefinition CommandDictionary::GenerateLanguageDefinition()
{
	TextEditor::LanguageDefinition langDef;

	langDef.mName = "Pix";

	langDef.mKeywords.insert("var");

	for (auto& [keyword, command] : mCommandMap)
	{
		TextEditor::Identifier id;
		id.mDeclaration = command->GetDescription();
		langDef.mIdentifiers.insert(std::make_pair(keyword, id));
	}

	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\$[a-zA-Z_]+", TextEditor::PaletteIndex::Keyword));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\'\\\\?[^\\']\\'", TextEditor::PaletteIndex::CharLiteral));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

	langDef.mCommentStart = "/*";
	langDef.mCommentEnd = "*/";
	langDef.mSingleLineComment = "//";

	langDef.mAutoIndentation = true;
	langDef.mCaseSensitive = true;

	return langDef;
}

Command* CommandDictionary::CommandLookup(const std::string& keyword)
{
	auto iter = mCommandMap.find(keyword);
	if (iter == mCommandMap.end())
		return nullptr;
	return iter->second.get();
}

template <class T>
void CommandDictionary::RegisterCommand()
{
	static_assert(std::is_base_of_v<Command, T>, "Invalid command type.");
	auto newCommand = std::make_unique<T>();
	mCommandMap.emplace(newCommand->GetName(), std::move(newCommand));
}