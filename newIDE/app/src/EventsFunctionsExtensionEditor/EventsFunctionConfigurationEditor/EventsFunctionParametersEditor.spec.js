// @flow
import { EventsFunctionParametersEditor } from './EventsFunctionParametersEditor';
import { ProjectScopedContainersAccessor } from '../../InstructionOrExpression/EventsScope';
import { makeTestProject } from '../../fixtures/TestProject';

const gd: libGDevelop = global.gd;

// This name is used internally by GDevelop and JavaScript.
const PROTECTED_PARAMETER_NAMES = ['Number'];

const getValidatedParameterName = (
    parameters: gdParameterMetadataContainer,
    projectScopedContainers: gdProjectScopedContainers,
    newName: string
): string => {
    const variablesContainersList = projectScopedContainers.getVariablesContainersList();
    const objectsContainersList = projectScopedContainers.getObjectsContainersList();
    const safeAndUniqueNewName = newName;
    if (PROTECTED_PARAMETER_NAMES.includes(newName)) {
        return 'ValidName';
    }
    return safeAndUniqueNewName;
};

describe('EventsFunctionParametersEditor', () => {
    let testProject;
    let project;
    let eventsFunction;
    let eventsFunctionsExtension;
    let projectScopedContainersAccessor;

    beforeEach(() => {
        testProject = makeTestProject(gd);
        project = testProject.project;
        eventsFunction = testProject.testEventsFunction;
        eventsFunctionsExtension = testProject.testEventsFunctionsExtension;
        projectScopedContainersAccessor = testProject.testSceneProjectScopedContainersAccessor;
    });

    afterEach(() => {
        project.delete();
    });

    test('allows using "number" as a parameter name', () => {
        const parameters = eventsFunction.getParameters();
        const parameter = parameters.insertNewParameter('ValidName', 0);
        parameter.setType('number');

        const validatedName = getValidatedParameterName(
            parameters,
            projectScopedContainersAccessor.get(),
            'number'
        );
        parameter.setName(validatedName);

        expect(parameter.getName()).toBe('number');
    });

    test('does not allow using "Number" as a parameter name', () => {
        const parameters = eventsFunction.getParameters();
        const parameter = parameters.insertNewParameter('ValidName', 0);
        parameter.setType('number');

        const validatedName = getValidatedParameterName(
            parameters,
            projectScopedContainersAccessor.get(),
            'Number'
        );
        parameter.setName(validatedName);

        expect(parameter.getName()).toBe('ValidName'); // Name should not change
    });

    test('allows using other names that are not "Number"', () => {
        const parameters = eventsFunction.getParameters();
        const parameter = parameters.insertNewParameter('ValidName', 0);
        parameter.setType('number');

        const validatedName = getValidatedParameterName(
            parameters,
            projectScopedContainersAccessor.get(),
            'MyParameter'
        );
        parameter.setName(validatedName);

        expect(parameter.getName()).toBe('MyParameter');
    });
});