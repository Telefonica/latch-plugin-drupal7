<?php

/*
  Latch Drupal 7 plugin - Integrates Latch into the Drupal 7 authentication process.
  Copyright (C) 2013 Eleven Paths

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

//Administration posible routes
function latch_admin($arguments) {
    switch ($arguments) {
        case 'settings':
            $content = latch_adminsettings();
            break;
    }
    return $content;
}

function latch_adminsettings() {
    $content = "<div>This is the page to set Latch configuration. To get register as a Latch application pleases visit: <a target='blank' href='http://latch.elevenpaths.com'>http://latch.elevenpaths.com</a></div><br>";
    $form_structure = build_settingsform();
    return $content . drupal_render($form_structure);;
}

//Form with the elements for the module config.
function settingsform($form_state) {
    //Getting stored values for settings.
    $appid = variable_get('latch_appid', ' ');
    $secret = variable_get('latch_secret', ' ');

    $form['appid'] = array(
        '#type' => 'textfield',
        '#title' => t('Application ID'),
        '#default_value' => $appid,
        '#suffix' => "</ul>",
        '#size' => 30,
        '#maxlength' => 20,
        '#required' => FALSE,
    );

    $form['secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Application Secret'),
        '#default_value' => $secret,
        '#suffix' => "</ul>",
        '#size' => 55,
        '#maxlength' => 40,
        '#required' => FALSE,
    );

    $form['save'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    return $form;
}

function build_settingsform() {
    return drupal_get_form('settingsform');
}

function settingsform_validate($form, &$form_state) {
    //TODO: Add validation for appId / Secret (Fixed length?)
}

function settingsform_submit($form, $form_state) {
    storeLatchSettings($form_state);
    drupal_goto("admin/settings/latch");
}

function storeLatchSettings(&$form_state) {
    variable_set('latch_appid', $form_state['values']['appid']);
    variable_set('latch_secret', $form_state['values']['secret']);
}

