#ifndef _REMOTESERVER_H
#define _REMOTESERVER_H

class RemoteServer {
private:
    char * settings;
    char * state;

    bool settingsValid;

    char user_name[128];
    char node_id[128];

public:

    /**
     * @brief   Constructs a Marijauto remote server connection with the given username and nodeid.
     * @param[in] _user_name The username of the owner of the Marijauto node represented by this RemoteServer.
     * @param[in] _node_id The secret key of the node represented by this RemoteServer.
     */
    RemoteServer(char * _user_name, char * _node_id);

    /**
     * @brief   Returns true if and only if settings have been dowloaded at least once from the server.
     * @details When this is false, there are no guarantees that any calls to 'getSetting_*' are correct.
     *          This can only change in one direction -- it will never reset from 'true' to 'false'.
     *          While there is no general way to guarantee that the latest settings are ALWAYS downloaded,
     *          if this returns 'true' it is guaranteed that the settings represent the server's settings at some point in the past.
     * @returns True IFF calls to 'getSetting_*' are correct for the server either now or at some time in the past.
     */
    bool areSettingsValid();

    /**
     * @brief   Returns the float value of the setting with the given name.
     * @details Settings are typically used to remotely control the device.
     *          These values can be changed by the user through the Marijauto server.
     * @param[in] name The name of the setting to retrieve.
     */
    float  getSetting_Float (char * name);

    /**
     * @brief   Returns the int value of the setting with the given name.
     * @details Settings are typically used to remotely control the device.
     *          These values can be changed by the user through the Marijauto server.
     * @param[in] name The name of the setting to retrieve.
     */
    int    getSetting_Int   (char * name);

    /**
     * @brief   Returns the bool value of the setting with the given name.
     * @details Settings are typically used to remotely control the device.
     *          These values can be changed by the user through the Marijauto server.
     * @param[in] name The name of the setting to retrieve.
     */
    bool   getSetting_Bool  (char * name);

    /**
     * @brief   Returns the String value of the setting with the given name.
     * @details Settings are typically used to remotely control the device.
     *          These values can be changed by the user through the Marijauto server.
     * @param[in] name The name of the setting to retrieve.
     */
    char *  getSetting_String(char * name);

    /**
     * @brief   Sets the remote state with the given name to the given float value.
     * @details Remote state is typically used to return sensor readings and other data.
     *          These values can be graphically displayed by the Marijauto server.
     * @param[in] name The name of the remote state to set.
     * @param[in] value The new float value of the remote state.
     */
    void setState(char * name, float  value);

    /**
     * @brief   Sets the remote state with the given name to the given int value.
     * @details Remote state is typically used to return sensor readings and other data.
     *          These values can be graphically displayed by the Marijauto server.
     * @param[in] name The name of the remote state to set.
     * @param[in] value The new int value of the remote state.
     */
    void setState(char * name, int    value);

    /**
     * @brief   Sets the remote state with the given name to the given bool value.
     * @details Remote state is typically used to return sensor readings and other data.
     *          These values can be graphically displayed by the Marijauto server.
     * @param[in] name The name of the remote state to set.
     * @param[in] value The new bool value of the remote state.
     */
    void setState(char * name, bool   value);

    /**
     * @brief   Sets the remote state with the given name to the given String value.
     * @details Remote state is typically used to return sensor readings and other data.
     *          These values can be graphically displayed by the Marijauto server.
     * @param[in] name The name of the remote state to set.
     * @param[in] value The new String value of the remote state.
     */
    void setState(char * name, char * value);

    /**
     * @brief   Sync this RemoteServer instance with the server.
     * @details This will upload any changes to the device's state to the server,
     *          and then download all of the settings from the server.
     */
    void syncWithRemoteServer();
};

#endif
