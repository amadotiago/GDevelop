/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */
#if defined(GD_IDE_ONLY) && !defined(GD_NO_WX_GUI)
#ifndef OBJECTSPROPGRIDHELPER_H
#define OBJECTSPROPGRIDHELPER_H

#include <wx/propgrid/propgrid.h>
#include <vector>
namespace gd { class MainFrameWrapper; }
namespace gd { class Object; }
namespace gd { class Project; }
namespace gd { class Layout; }

namespace gd
{

/**
 * \brief Helper class used to easily use a wxPropertyGrid so as to view and edit the properties of
 * a gd::Object.
 *
 * \see gd::Object
 *
 * \ingroup IDEdialogs
 */
class GD_CORE_API ObjectsPropgridHelper
{
public:

    /**
     * \brief Default constructor.
     * \param project The project edited
     * \param layout The layout being edited
     */
    ObjectsPropgridHelper(gd::Project & project_, gd::MainFrameWrapper & mainFrameWrapper_) : grid(NULL), project(project_), mainFrameWrapper(mainFrameWrapper_) {};
    virtual ~ObjectsPropgridHelper() {};

    /**
     * \brief Refresh the property grid from an object
     * \param object The object to be displayed.
     * \param displayedAfterInstanceProperties If set to true, it is assumed that the grid already contains properties of an instance of the object.
     */
    void RefreshFrom(const gd::Object * object, bool displayedAfterInstanceProperties = false);

    /**
     * \brief Call this when the event wxEVT_PG_SELECTED of wxPropertyGrid is triggered.
     * \param object The object displayed
     * \param layout The layout the object belongs to ( or the layout being edited for global objects )
     * \param event The event generated by wxWidgets.
     * \return true if the grid must be updated
     */
    bool OnPropertySelected(gd::Object * object, gd::Layout * layout, wxPropertyGridEvent& event);

    /**
     * \brief Call this when the event wxEVT_PG_CHANGED of wxPropertyGrid is triggered.
     * \param object The object displayed
     * \param layout The layout the object belongs to ( or the layout being edited for global objects )
     * \param event The event generated by wxWidgets.
     * \return true if the grid must be updated
     */
    bool OnPropertyChanged(gd::Object * object, gd::Layout * layout, wxPropertyGridEvent& event);

    /**
     * \brief Set the grid being used.
     */
    void SetGrid(wxPropertyGrid * grid_) { grid = grid_; }

private:

    /**
     * \brief A common task when a changes have been made is to update the shared data of automatisms,
     * which are stored in layouts.
     */
    void UpdateAutomatismsSharedData(gd::Project & project, gd::Layout * layout) const;

    wxPropertyGrid * grid; ///< The grid used for diplaying and editing properties.
    gd::Project & project;
    gd::MainFrameWrapper & mainFrameWrapper;
};

}

#endif // OBJECTSPROPGRIDHELPER_H
#endif
