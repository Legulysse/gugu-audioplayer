
-- Setup the include path of the engine build scripts directory
package.path = package.path .. ";../GuguEngine/Tools/Build/?.lua"

require "PremakeUtility"


-- Solution Configuration
local pathDev 		= EnsureSlash("../Dev")
local pathVersion 	= EnsureSlash("../Version")

BuildCfg = SetupBuildCfg("../GuguEngine")


-- Build Solution
solution "AudioPlayer"
    IncludeDefaultSolutionDefinition(BuildCfg, pathDev.."Build")

    -- GUIDs can be generated from here : https://www.guidgenerator.com/online-guid-generator.aspx
    package.guid = "BEBB4888-E0C7-482A-9304-DD406237C589"

    group "Application"
    ProjectDefault(BuildCfg, "GuguAudioPlayer", pathDev.."Sources", pathVersion, "6A983AD1-4D36-4949-B95D-B2FA4E7BC81D")
    
        -- Resources (Icon)
        filter { 'system:windows' }
            files {
                pathDev.."Sources/AppResources/**.rc",
                pathDev.."Sources/AppResources/**.ico",
            }
            vpaths { ["Resources/*"] = { "**.rc", "**.ico" } }
        filter {}

    group "Engine"
    ProjectLibGuguEngine(BuildCfg)
    
    group "Externals"
    ProjectLibSFML(BuildCfg)
    ProjectLibPugiXml(BuildCfg)
    ProjectLibImGui(BuildCfg)
